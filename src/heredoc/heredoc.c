/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:04:44 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/18 22:55:54 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*expand_var_heredoc(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			str = expand_var2(str, i);
	}
	return (str);
}

static char	*heredoc_error(char *delimiter, char *heredoc, int line_count)
{
	ft_safe_free((void **)&heredoc);
	ft_putstr_fd("heredoc: warning: here-document at line ", 2);
	ft_putnbr_fd(line_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	g_main.is_cmd_running = 0;
	g_main.status = 0;
	return (NULL);
}

char	*name_heredoc(int reset)
{
	char		*name;
	char		*num;
	char		*tmp;
	static int	i;

	if (i == 0)
		i = 1;
	if (reset)
	{
		i = 1;
		return (NULL);
	}
	num = ft_itoa(i);
	while (ft_strlen(num) < 3)
	{
		tmp = ft_strjoin("0", num);
		ft_safe_free((void **)&num);
		num = tmp;
	}
	name = ft_strjoin("heredoc", tmp);
	ft_safe_free((void **)&tmp);
	i++;
	return (name);
}

static char	*save_heredoc(char *delim, char *heredoc)
{
	int		fd;
	char	*tmp;
	char	*name;

	name = name_heredoc(0);
	tmp = expand_var_heredoc(ft_strdup(heredoc));
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, tmp, ft_strlen(tmp) - ft_strlen(delim) - 1);
	close(fd);
	ft_safe_free((void **)&tmp);
	return (name);
	// fd = open("./heredoc", O_RDONLY);
	// dup2(fd, 0);
	// close(fd);
}

char	*heredoc(char *delimiter)
{
	char	*line;
	char	*heredoc;
	char	*name;
	int		line_count;

	g_main.is_cmd_running = 1;
	heredoc = ft_strdup("");
	line_count = 0;
	while (1)
	{
		line_count++;
		line = readline("> ");
		if (!line)
			return (heredoc_error(delimiter, heredoc, line_count));
		heredoc = ft_strjoin_free(heredoc, line);
		heredoc = ft_strjoin_free(heredoc, "\n");
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_safe_free((void **)&line);
	}
	name = save_heredoc(delimiter, heredoc);
	g_main.line = ft_strjoin_free(g_main.line, "\n");
	g_main.line = ft_strjoin_free(g_main.line, heredoc);
	ft_safe_free((void **)&heredoc);
	g_main.is_cmd_running = 0;
	g_main.status = 0;
	return (name);
}
