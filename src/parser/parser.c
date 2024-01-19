/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:54:49 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/19 00:01:07 by renato           ###   ########.fr       */
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
		if (tmp->type == WORD && tmp->next->type != PIPE && move)
		{
			move = FALSE;
			hold = tmp;
			move_cmd(hold);
		}
		tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			move = TRUE;
	}
	while (tmp && tmp->prev)
		tmp = tmp->prev;
}

static void	fd_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_main.status = 1;
}

static void	check_outfile(t_cmd *cmd, t_cmd *tmp)
{
	int	fd;

	fd = 0;
	if (tmp->type == APPEND)
		fd = open(tmp->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (tmp->type == OUTFILE)
		fd = open(tmp->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		fd_error(tmp->args[0]);
		return ;
	}
	if (cmd->outfile)
		ft_safe_free((void **)&cmd->outfile);
	cmd->outfile = ft_strjoin_free(getcwd(NULL, 0), "/");
	cmd->outfile = ft_strjoin_free(cmd->outfile, tmp->args[0]);
	close(fd);
}

//The function set_output() is called from parser.c
//It runs through the command list and checks for output redirections
//If it finds one, it calls check_outfile() to check if the file exists 
//and is accessible. If the file exists and is accessible, it saves 
//the path of the file in cmd->outfile. It also saves the  current 
//redirection type in cmd->redir[1]
//redir[0] is used for input redirections
//redir[1] is used for output redirections

void	set_output(void)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = g_main.cmd_list;
	while (cmd && cmd->type != WORD)
		cmd = cmd->next;
	tmp = g_main.cmd_list;
	while (tmp)
	{
		if (tmp->type == OUTFILE)
		{
			check_outfile(cmd, tmp);
			cmd->redir[1] = OUTFILE;
		}
		else if (tmp->type == APPEND)
		{
			check_outfile(cmd, tmp);
			cmd->redir[1] = APPEND;
		}
		tmp = tmp->next;
	}
}

static void	check_infile(t_cmd *cmd, t_cmd *tmp)
{
	int	fd;

	fd = 0;
	if (!cmd)
		return ;
	if (tmp->type == HEREDOC)
	{
		fd = open(tmp->args[0], O_RDONLY, 0644);
		if (fd == -1)
		{
			fd_error("heredoc");
			return ;
		}
	}
	else if (tmp->type == INFILE)
	{
		fd = open(tmp->args[0], O_RDONLY, 0644);
		if (fd == -1)
		{
			fd_error(tmp->args[0]);
			return ;
		}
	}
	if (cmd->infile)
		ft_safe_free((void **)&cmd->infile);
	cmd->infile = ft_strjoin_free(getcwd(NULL, 0), "/");
	// if (tmp->type == HEREDOC)
	// 	cmd->infile = ft_strjoin_free(cmd->infile, "heredoc");
	// else if (tmp->type == INFILE)
		cmd->infile = ft_strjoin_free(cmd->infile, tmp->args[0]);
	close(fd);
}

void	set_input(void)
{
	t_cmd	*tmp;
	t_cmd	*cmd;
	char	*name;

	cmd = g_main.cmd_list;
	while (cmd && cmd->type != WORD)
		cmd = cmd->next;
	tmp = g_main.cmd_list;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			check_infile(cmd, tmp);
			if (cmd)
				cmd->redir[0] = INFILE;
		}
		else if (tmp->type == HEREDOC)
		{
			name = heredoc(tmp->args[0]);
			ft_safe_free((void **)&tmp->args[0]);
			tmp->args[0] = name;
			check_infile(cmd, tmp);
			if (cmd)
				cmd->redir[0] = HEREDOC;
		}
		tmp = tmp->next;
	}
}

void	remove_redir(void)
{
	t_cmd	*tmp;

	tmp = g_main.cmd_list;
	while (tmp)
	{
		if ((tmp->type == INFILE || tmp->type == OUTFILE || tmp->type == APPEND
				|| tmp->type == HEREDOC) && tmp->next)
		{
			tmp->next->prev = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				g_main.cmd_list = tmp->next;
			free_tab(tmp->args);
			ft_safe_free((void **)&tmp->name);
			ft_safe_free((void **)&tmp);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

int	parser(void)
{
	arrange_cmd_list();
	set_output();
	set_input();
	remove_redir();
	return (0);
}
