/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:46:07 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/28 14:28:49 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

# define TABLE_SIZE 256
# define FALSE 0
# define TRUE 1
# define REMOVE 1
# define NAME 0

typedef enum s_token_type
{
	WORD,
	APPEND,
	HEREDOC,
	OUTFILE,
	INFILE,
	AND,
	OR,
	PIPE
}	t_token_type;

typedef enum s_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;


//--Structs--//
//Token list

typedef struct s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//Command list

typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*infile;
	char			*outfile;
	int				argc;
	int				redir[2];
	int				fd[2];
	int				type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

//Cmd_info

typedef struct s_cmd_info
{
	char	*path;
	int		heredoc;
	int		heredoc_count;
	int		infile;
	int		outfile;
	int		append;
}	t_cmd_info;

//pipe_info
typedef struct s_pipes
{
	int				pipes[2];
	int				used;
}					t_pipes;

typedef struct s_pipe_info
{
	char	*path;
	int		pipe_counter;
	int		fd1[2];
//	t_pipes *fd2;
//	t_pipes *fd3;
} 			t_pipe_info;
//Hashtable

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//Main

typedef struct s_main
{
	t_env		*env_var[TABLE_SIZE];
	t_token		*token_list;
	t_cmd		*cmd_list;
	t_cmd_info	cmd_info;
	t_pipe_info *pipe;
	char		**envp;
	char		*line;
	int			open_quote;
	int			status;
	int			is_cmd_running;
	int			signal_received;
}	t_main;


//Global variable

extern t_main	g_main;

//EXIT------------------------------------------
//exit.c

void	ft_exit(char **args, int argc);
void	ft_exit2(void);
int		adjust_status(int status);

//INIT------------------------------------------
//init.c

void	init_hashtable(t_env **env_var);
void	init_global(char **env);

//SIGNALS---------------------------------------
//signal.c

int		signal_set(void);
void	handler(int sig);

//PARSER----------------------------------------
//lexer.c

int		lexer(char **str);

//tokenizer.c

char	*tokenizer(char *str);
int		check_quote(int quote, char c);

//token_utils.c

void	clear_token_list(void);
void	add_token(char *name, int type);
t_token	*new_token(char *name, int type);

//cmd_list.c

void	create_cmd_list(void);
void	clear_cmd_list(void);

//cmd_list_utils.c

t_cmd	*new_cmd(char *name, int type);
void	add_cmd(t_cmd *cmd);
void	clear_cmd_list(void);
void	print_cmd_list(void); //test function

//expand_var.c

char	*expand_var(char *name);
char	*expand_var2(char *str, int *i);

//parser.c

int		parser(void);

//EXEC------------------------------------------
//builtin.c

int		exec_builtin(t_cmd *cmd);

//execute.c

void	exec_cmd(t_cmd *cmd);
void	execute_cmd_list(void);
char	*check_path(char *name);
void	exec(t_cmd *cmd, char *path);
int		check_if_builtin(char *name);
void	set_fd(t_cmd *cmd);

//BUILTINS--------------------------------------
//export.c

int		ft_export(char **args, int argc);

//echo.c

int		ft_echo(char **args, int fd);

//cd.c

int		ft_cd(char **args);

//HASHTABLE-------------------------------------
//hashtable.c

int		hash(char *key);
int		update_key(t_env **env_var, char *key, char *value);
t_env	*search(t_env **env_var, char *key);
char	*search_value(t_env **env_var, char *key);
void	clear_hashtable(t_env **env_var);
void	delete_key(t_env **env_var, char *key);
void	insert_key(t_env **env_var, char *key, char *value);

//ENV-------------------------------------------
//set_env.c

int		set_env(t_env **env_var, char **env);
int		free_tab(char **tab);

//HEREDOC---------------------------------------
//heredoc.c

char	*heredoc(char *delimiter);
char	*heredoc_files(int flag);

//heredoc_utils.c

int		remove_heredoc(int last);
void	heredoc_signal(int sig);
void	heredoc_exit(int status);

//heredoc_utils2.c

char	*expand_var_heredoc(char *str);
char	*heredoc_error(char *delimiter, int line_count);
char	*save_heredoc(char *delim, char *heredoc);

//PIPE------------------------------------------
//pipe.c
void ig_pipe(t_cmd *cmd);

//------------------TEST FUNCTIONS-----------------------
//------------------TEST FUNCTIONS-----------------------
void	print_hashtable(t_env **env_var);

#endif //SHELL_H