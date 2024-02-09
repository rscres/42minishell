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
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

# define SETPROMPT "\001\e[9;35m\002"
# define SET "\001\e[5;33m\002"
# define RESET   "\001\e[0m\002"

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

//pipe_info

typedef struct s_pipe_info
{
	char	*path;
	int		pipe_counter;
	int		fd1[2];
}	t_pipe_info;

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
	t_pipe_info	*pipe;
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
int		adjust_status(int status);

//INIT------------------------------------------
//init.c

void	init_global(char **env);
void	init_shell(char **env);

//SIGNALS---------------------------------------
//signal.c

int		signal_set(void);
void	sigint(int sig);
void	sigquit(int sig);

//PARSER----------------------------------------
//lexer.c

int		lexer(char **str);
int		get_type(char *str);

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
int		get_argc(t_token *tmp);

//expand_var.c

char	*expand_var(char *name);
char	*expand_var2(char *str, int *i);

//expand_var_utils.c

char	*remove_dollar(char	*var);
char	*get_var_name(const char *str);
char	*insert_value(char *str, char *value, int name_len, int pos);
int		close_single_quote(char *str, int *i, int *quote);

//parser.c

int		parser(void);

//parser_utils.c

void	arrange_cmd_list(void);
void	fd_error(char *str);
void	remove_redir(void);
void	ig_path_builtin(void);

//set_redirects_utils.c

int		check_outfile(t_cmd *cmd, t_cmd *tmp);
int		save_input_file(t_cmd *cmd, t_cmd *tmp);
void	change_cmd(t_cmd **cmd, t_cmd **tmp);
void	set_heredoc(t_cmd *cmd, t_cmd *tmp);

//EXEC------------------------------------------
//builtin.c

int		exec_builtin(t_cmd *cmd);

//execute.c

void	exec_cmd(t_cmd *cmd);
void	execute_cmd_list(void);
void	exec(t_cmd *cmd, char *path);
void	set_fd(t_cmd *cmd);
int		file_dir_check(t_cmd *cmd);
int		ig_is_redir(char *name);

//execute_utils.c

int		file_dir_check(t_cmd *cmd);
int		is_directory(const char *path);
int		check_if_builtin(char *name);
char	*check_path(char *name);

//BUILTINS--------------------------------------
//export.c

int		ft_export(char **args, int argc, int fd);
char	**split_var(char *var);
int		is_valid_char(char *str);

//export_print.c

char	**save_table_to_array(void);
void	print_vars(int fd);

//echo.c

int		ft_echo(char **args, int fd);

//cd.c

int		ft_cd(char **args);

//unset.c

int		ft_unset(char **args);

//pwd.c

int		ft_pwd(int fd);

//pipe.c
void	ig_middle_born(t_cmd *cmd, int fd);
void	ig_pipe_fd(t_cmd *cmd, int fd);
void	ig_pipe_exc(t_cmd *cmd, int fd_read);
void	ig_pipe_closer(void );
void	ig_pipe_handler(t_cmd *cmd);
void	ig_close_linked(void);

//ENV-------------------------------------------
//set_env.c

int		set_env(t_env **env_var, char **env);
int		free_tab(char **tab);
int		ft_env(int fd);

//HASHTABLE-------------------------------------
//hashtable.c

int		hash(char *key);
int		update_key(t_env **env_var, char *key, char *value);
t_env	*search(t_env **env_var, char *key);
char	*search_value(t_env **env_var, char *key);
void	print_hashtable(t_env **env_var, int fd);

//hashtable_utils.c

void	clear_hashtable(t_env **env_var);
void	delete_key(t_env **env_var, char *key);
void	insert_key(t_env **env_var, char *key, char *value);

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

void	ig_pipe(t_cmd *cmd);

//ERROR-----------------------------------------
//error.c

int		ft_error(char *str, char *msg, int err);
int		syntax_error(char *str);

#endif //SHELL_H