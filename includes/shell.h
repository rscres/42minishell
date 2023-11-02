/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:46:07 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/02 12:16:35 by rseelaen         ###   ########.fr       */
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

# define TABLE_SIZE 196

typedef enum s_token_type
{
	WORD,
	DOUBLE_GREATER_THAN,
	DOUBLE_LESS_THAN,
	GREATER_THAN,
	LESS_THAN,
	AND,
	OR,
	PIPE
}	t_token_type;

//Structs
//token
typedef struct s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

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
	t_token	*tokens;
}	t_main;

//Parsing
//parser.c


//Signals
int	signal_set(void);

//Hashtable
int	hash_funtion(char *key);

#endif //SHELL_H