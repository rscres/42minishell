/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:54:49 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/08 21:06:48 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	set_output(t_cmd *tmp, t_cmd *cmd)
{
	if (cmd && (tmp->type == WORD || tmp->type == PIPE) && tmp->next)
		change_cmd(&cmd, &tmp);
	if (tmp->type == OUTFILE)
	{
		if (check_outfile(cmd, tmp))
		{
			tmp = cmd;
			return (1);
		}
		else if (cmd)
			cmd->redir[1] = OUTFILE;
	}
	else if (tmp->type == APPEND)
	{
		if (check_outfile(cmd, tmp))
		{
			tmp = cmd;
			return (1);
		}
		else if (cmd)
			cmd->redir[1] = APPEND;
	}
	return (0);
}

static int	set_input(t_cmd	*tmp, t_cmd	*cmd)
{
	int	set;

	set = 0;
	if (tmp->type == INFILE && !set)
	{
		set = save_input_file(cmd, tmp);
		if (access(cmd->infile, R_OK))
		{
			tmp = cmd;
			fd_error(cmd->infile);
		}
		else if (cmd)
			cmd->redir[0] = INFILE;
	}
	else if (tmp->type == HEREDOC)
	{
		set_heredoc(cmd, tmp);
	}
	return (set);
}

static void	set_input_output(void)
{
	t_cmd	*tmp;
	t_cmd	*cmd;
	int		error;

	cmd = g_main.cmd_list;
	error = 0;
	while (cmd && cmd->type != WORD && cmd->type != PIPE)
		cmd = cmd->next;
	tmp = g_main.cmd_list;
	while (tmp)
	{
		if (cmd && (((tmp->type == WORD || tmp->type == PIPE) && tmp->next)
				|| error))
		{
			change_cmd(&cmd, &tmp);
			error = 0;
		}
		if (tmp->type == INFILE || tmp->type == HEREDOC)
			error = set_input(tmp, cmd);
		else if (tmp->type == OUTFILE || tmp->type == APPEND)
			error = set_output(tmp, cmd);
		tmp = tmp->next;
		if (tmp && tmp->type == WORD && !tmp->next)
			break ;
	}
}

int	parser(void)
{
	arrange_cmd_list();
	set_input_output();
	remove_redir();
	ig_path_builtin();
	return (0);
}
