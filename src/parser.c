/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:54:49 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/30 18:16:43 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	move_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	while (tmp->next && tmp->next->type != PIPE)
		tmp = tmp->next;
	if (tmp->next)
		cmd->next = tmp->next;
	else
		cmd->next = NULL;
	tmp->next = cmd;
	cmd->prev = tmp;
}

void	arrange_cmd_list(void)
{
	t_cmd	*tmp;
	t_cmd	*hold;
	int		move;

	tmp = g_main.cmd_list;
	move = TRUE;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->next && move)
		{
			move = FALSE;
			hold = tmp;
			move_cmd(hold);
			while (tmp->next && tmp->next->type != PIPE)
				tmp = tmp->next;
		}
		tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			move = TRUE;
	}

}

int	parser(void)
{
	arrange_cmd_list();
	return (0);
}
