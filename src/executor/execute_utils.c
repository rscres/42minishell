/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:38:29 by renato            #+#    #+#             */
/*   Updated: 2024/02/09 14:27:55 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*check_path(char *name)
{
	char		*path;
	char		**paths;
	int			i;

	i = -1;
	path = search_value(g_main.env_var, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free(path, name);
		if (!access(path, F_OK))
		{
			free_tab(paths);
			return (path);
		}
		ft_safe_free((void **)&path);
	}
	free_tab(paths);
	return (ft_strdup(name));
}

int	check_if_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}

int	check_infile(t_cmd *cmd)
{
	int		fd;

	fd = 0;
	if (cmd && cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (access(cmd->infile, R_OK))
			return (1);
		if (fd == -1)
		{
			ft_error(cmd->infile, NULL, 1);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	file_dir_check(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	if (check_infile(cmd))
		return (1);
	if (cmd->outfile)
	{
		fd = open(cmd->outfile, O_RDONLY);
		if (access(cmd->outfile, W_OK))
			return (1);
		if (fd == -1)
		{
			ft_error(cmd->outfile, NULL, 1);
			return (1);
		}
		close(fd);
	}
	if (cmd && is_directory(cmd->name))
	{	
		ft_error(cmd->name, "is a directory", 126);
		return (1);
	}
	return (0);
}
