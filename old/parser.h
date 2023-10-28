/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:19:06 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/26 20:15:12 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_cmd
{
	char			*name;
	int				heredoc;
	int				infile;
	int				outfile;
	t_arg			*args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

t_cmd	*parser(char *line);

#endif //PARSER_H