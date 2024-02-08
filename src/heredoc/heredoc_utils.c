/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:20:54 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/05 22:32:14 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*create_suffix(int i)
{
	char	*suffix;
	char	*tmp;

	suffix = ft_itoa(i);
	while (ft_strlen(suffix) < 3)
	{
		tmp = ft_strjoin("0", suffix);
		ft_safe_free((void **)&suffix);
		suffix = tmp;
	}
	return (suffix);
}

int	remove_heredoc(int last)
{
	char	*cur_file;
	char	*suffix;
	int		i;
	int		fd;

	i = 1;
	while (i < last)
	{
		suffix = create_suffix(i);
		cur_file = ft_strjoin("/tmp/heredoc", suffix);
		ft_safe_free((void **)&suffix);
		fd = open(cur_file, O_RDONLY);
		close(fd);
		if (fd != -1)
			unlink(cur_file);
		ft_safe_free((void **)&cur_file);
		i++;
	}
	return (0);
}

char	*heredoc_files(int flag)
{
	char		*name;
	char		*num;
	static int	i;

	if (i == 0)
		i = 1;
	if (flag == REMOVE)
	{
		remove_heredoc(i);
		i = 1;
		return (NULL);
	}
	num = create_suffix(i);
	name = ft_strjoin("/tmp/heredoc", num);
	ft_safe_free((void **)&num);
	i++;
	return (name);
}

void	heredoc_exit(int status)
{
	clear_hashtable(g_main.env_var);
	clear_token_list();
	clear_cmd_list();
	ft_safe_free((void **)&g_main.pipe);
	free(g_main.line);
	exit(status);
}

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		(void)signal;
		g_main.signal_received = TRUE;
		g_main.status = 130;
		close(0);
		ft_putchar_fd('\n', 1);
	}
}
