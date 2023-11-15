/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:46:07 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/15 01:23:38 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define TABLE_SIZE 256

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

//Structs
//token list
typedef struct s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//command list
typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				argc;
	struct s_cmd	*next;
}	t_cmd;

//hashtable
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//Main
typedef struct s_main
{
	t_env	*env_var[TABLE_SIZE];
	t_token	*token_list;
	int		open_quote;
	t_cmd	*cmd_list;
}	t_main;

//Global variable
extern t_main	g_main;

//EXIT
//main.c
void	ft_exit(int status);

//INIT
//init.c
void	init_hashtable(t_env **env_var);
void	init_global(void);

//SIGNALS
//signal.c
int		signal_set(void);

//PARSER
//parser.c
int		parse_line(char **str);

//tokenizer.c
char	*tokenizer(char *str);

//token_utils.c
void	clear_token_list(void);
void	add_token(char *name, int type);
t_token	*new_token(char *name, int type);

//cmd_list.c
void	create_cmd_list(void);
void	clear_cmd_list(void);

//EXEC
//builtin.c
int		exec_builtin(char *name, char **args);

//HaASHTABLE
//hashtable.c
int		hash(char *key);
t_env	*search(t_env **env_var, char *key);
void	clear_hashtable(t_env **env_var);
void	delete_key(t_env **env_var, char *key);
void	insert_key(t_env **env_var, char *key, char *value);

//ENV
//set_env.c
int		set_env(t_env **env_var, char **env);
int		free_tab(char **tab);

//------------------TEST FUNCTIONS-----------------------
//------------------TEST FUNCTIONS-----------------------
void	print_hashtable(t_env **env_var);

#endif //SHELL_H