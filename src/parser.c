/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:54:49 by rseelaen          #+#    #+#             */
/*   Updated: 2023/12/18 15:14:30 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	move_cmd(t_cmd *cmd)
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
		cmd->next = tmp->next;
	else
		cmd->next = NULL;
	// print_cmd_list();
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
	while (tmp && tmp->next)
	{
		if (tmp->type == WORD && tmp->next && move)
		{
			move = FALSE;
			hold = tmp;
			move_cmd(hold);
			// while (tmp->next && tmp->next->type != PIPE)
			// 	tmp = tmp->next;
		}
		tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			move = TRUE;
	}
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	// print_cmd_list();
	g_main.cmd_list = tmp;
}

void	set_output(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp && tmp->type != WORD)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == OUTFILE)
		{
			tmp->fd_out = open(tmp->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp->fd_out == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->args[0], 2);
				ft_putstr_fd(": ", 2);
				// ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				g_main.status = 1;
				return ;
			}
		}
		if (tmp->type == APPEND)
		{
			tmp->fd_out = open(tmp->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tmp->fd_out == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->args[0], 2);
				ft_putstr_fd(": ", 2);
				// ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				g_main.status = 1;
				return ;
			}
		}
		tmp = tmp->prev;
	}
}

void	set_input(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->type != WORD)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			tmp->fd_in = open(tmp->args[0], O_RDONLY);
			if (tmp->fd_in == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->args[0], 2);
				ft_putstr_fd(": ", 2);
				// ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				g_main.status = 1;
				return ;
			}
		}
		if (tmp->type == HEREDOC)
			return ;
		tmp = tmp->prev;
	}
}

int	parser(void)
{
	print_cmd_list();
	arrange_cmd_list();
	set_output(g_main.cmd_list);
	// set_input(g_main.cmd_list);
	print_cmd_list();
	return (0);
}
