/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:21:59 by renato            #+#    #+#             */
/*   Updated: 2024/02/08 21:08:28 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	check_outfile(t_cmd *cmd, t_cmd *tmp)
{
	int	fd;
	int	ret;

	fd = 0;
	ret = 0;
	if (tmp->type == APPEND)
		fd = open(tmp->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (tmp->type == OUTFILE)
		fd = open(tmp->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || access(tmp->args[0], W_OK | R_OK))
	{
		fd_error(tmp->args[0]);
		ret = 1;
	}
	if (cmd)
	{
		if (cmd->outfile)
			ft_safe_free((void **) &cmd->outfile);
		cmd->outfile = ft_strjoin_free(getcwd(NULL, 0), "/");
		cmd->outfile = ft_strjoin_free(cmd->outfile, tmp->args[0]);
	}
	close(fd);
	return (ret);
}

void	change_cmd(t_cmd **cmd, t_cmd **tmp)
{
	*cmd = (*tmp)->next;
	if ((*cmd)->type == PIPE)
		*cmd = (*cmd)->next;
	while (*cmd && (*cmd)->type != WORD && (*cmd)->type != PIPE)
		*cmd = (*cmd)->next;
	*tmp = (*tmp)->next;
}

int	save_input_file(t_cmd *cmd, t_cmd *tmp)
{
	int	fd;

	fd = 0;
	if (!cmd)
		return (0);
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
	if (fd < 0 || access(tmp->args[0], R_OK))
		return (1);
	return (0);
}

void	set_heredoc(t_cmd *cmd, t_cmd *tmp)
{
	char	*name;

	name = heredoc(tmp->args[0]);
	ft_safe_free((void **)&tmp->args[0]);
	tmp->args[0] = name;
	save_input_file(cmd, tmp);
	if (cmd)
		cmd->redir[0] = HEREDOC;
}
