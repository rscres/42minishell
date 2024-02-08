/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:34:26 by renato            #+#    #+#             */
/*   Updated: 2024/02/07 22:12:12 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	fd_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_main.status = 1;
}

static void	move_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		g_main.cmd_list = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	while (tmp->next && tmp->next->type != PIPE)
		tmp = tmp->next;
	if (tmp->next)
	{
		cmd->next = tmp->next;
		tmp->next->prev = cmd;
	}
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
	g_main.pipe->pipe_counter = 0;
	while (tmp && tmp->next)
	{
		if (tmp->type == WORD && tmp->next->type != PIPE && move)
		{
			move = FALSE;
			hold = tmp;
			move_cmd(hold);
		}
		tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
		{
			g_main.pipe->pipe_counter++;
			move = TRUE;
		}
	}
	while (tmp && tmp->prev)
		tmp = tmp->prev;
}

void	remove_redir(void)
{
	t_cmd	*tmp;

	tmp = g_main.cmd_list;
	while (tmp)
	{
		while ((tmp->type == INFILE || tmp->type == OUTFILE
				|| tmp->type == APPEND || tmp->type == HEREDOC) && tmp->next)
		{
			tmp->next->prev = tmp->prev;
			if (tmp->prev)
			{
				tmp->prev->next = tmp->next;
			}
			else
			{
				g_main.cmd_list = tmp->next;
			}
			free_tab(tmp->args);
			ft_safe_free((void **)&tmp->name);
			ft_safe_free((void **)&tmp);
			tmp = g_main.cmd_list;
		}
		tmp = tmp->next;
	}
}

void	ig_path_builtin(void)
{
	t_cmd	*tmp;
	char	*pos;

	tmp = g_main.cmd_list;
	while (tmp)
	{
		if (tmp->type == WORD && !check_if_builtin(tmp->name))
		{
			pos = ft_strrchr(tmp->name, '/');
			if (pos && check_if_builtin(pos + 1))
			{
				pos = ft_strdup(ft_strrchr(tmp->name, '/') + 1);
				ft_safe_free((void **)&tmp->name);
				tmp->name = pos;
			}
		}
		tmp = tmp->next;
	}
}
