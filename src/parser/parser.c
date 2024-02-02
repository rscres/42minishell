/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:54:49 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/02 12:38:20 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		if (tmp->type == WORD && tmp->next)
		{
			cmd = tmp->next;
			while (cmd && cmd->type != WORD)
				cmd = cmd->next;
			tmp = tmp->next;
		}
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

static void	save_input_file(t_cmd *cmd, t_cmd *tmp)
{
	int	fd;

	fd = 0;
	if (!cmd)
		return ;
	fd = open(tmp->args[0], O_RDONLY, 0644);
	if (cmd->infile)
		ft_safe_free((void **)&cmd->infile);
	if (tmp->type == HEREDOC)
		cmd->infile = ft_strdup(tmp->args[0]);
	else
	{
		cmd->infile = ft_strjoin_free(getcwd(NULL, 0), "/");
		if (tmp->args[0][0] == '.')
			cmd->infile = ft_strjoin_free(cmd->infile, tmp->args[0] + 1);
		else
			cmd->infile = ft_strjoin_free(cmd->infile, tmp->args[0]);
	}
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
		if (tmp->type == WORD && tmp->next)
		{
			cmd = tmp->next;
			while (cmd && cmd->type != WORD)
				cmd = cmd->next;
			tmp = tmp->next;
		}
		if (tmp->type == INFILE)
		{
			save_input_file(cmd, tmp);
			if (cmd)
				cmd->redir[0] = INFILE;
		}
		else if (tmp->type == HEREDOC)
		{
			name = heredoc(tmp->args[0]);
			ft_safe_free((void **)&tmp->args[0]);
			tmp->args[0] = name;
			save_input_file(cmd, tmp);
			if (cmd)
				cmd->redir[0] = HEREDOC;
		}
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
