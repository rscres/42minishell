/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:30:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/26 20:32:54 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_closed_quotes(char *line)
{
	int	open = 0;
	int	quote = 0;

	while (*line)
	{
		if (*line == '\"' && open == 0)
		{
			quote = 1;
			open = 1;
		}
		if (*line == '\'' && open == 0)
		{
			quote = 2;
			open = 1;
		}
		else if ((*line == '\"' && open == 1 && quote == 1)
			|| (*line == '\'' && open == 1 && quote == 2))
		{
			quote = 0;
			open = 0;
		}
		line++;
	}
	return (open);
}

t_cmd	*parser(char *line)
{
	t_cmd	cmd;
	int		i = 0;
	int		j = 0;
	int		cmd = 1;

	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
		{
			j = i;
			while (!is_whitespace(line[j]))
				j++;
			cmdlst_add_back(&cmd, cmdlst_new());
			break ;
		}
		i++;
	}
	return (&cmd);
}
