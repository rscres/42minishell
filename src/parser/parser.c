/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:54:49 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/06 19:08:21 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	set_output(void)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = g_main.cmd_list;
	while (cmd && cmd->type != WORD && cmd->type != PIPE)
		cmd = cmd->next;
	tmp = g_main.cmd_list;
	while (tmp)
	{
		if ((tmp->type == WORD || cmd->type == PIPE) && tmp->next)
			change_cmd(&cmd, &tmp);
		if (tmp->type == OUTFILE)
		{
			if (check_outfile(cmd, tmp))
			{
				tmp = cmd;
				continue ;
			}
			cmd->redir[1] = OUTFILE;
		}
		else if (tmp->type == APPEND)
		{
			if (check_outfile(cmd, tmp))
			{
				tmp = cmd;
				continue ;
			}
			cmd->redir[1] = APPEND;
		}
		tmp = tmp->next;
	}
}

static void	set_input(void)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = g_main.cmd_list;
	while (cmd && cmd->type != WORD && cmd->type != PIPE)
		cmd = cmd->next;
	tmp = g_main.cmd_list;
	while (tmp)
	{
		if ((tmp->type == WORD || cmd->type == PIPE) && tmp->next)
			change_cmd(&cmd, &tmp);
		if (tmp->type == INFILE)
		{
			save_input_file(cmd, tmp);
			if (access(cmd->infile, R_OK))
			{
				tmp = cmd;
				continue ;
			}
			if (cmd)
				cmd->redir[0] = INFILE;
		}
		else if (tmp->type == HEREDOC)
			set_heredoc(cmd, tmp);
		tmp = tmp->next;
	}
}

int	parser(void)
{
	arrange_cmd_list();
	set_input();
	set_output();
	remove_redir();
	return (0);
}
