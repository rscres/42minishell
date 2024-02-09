/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:08:53 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/09 13:53:23 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*expand_var_heredoc(char *str)
{
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			str = expand_var2(str, &i);
	}
	return (str);
}

char	*heredoc_error(char *delimiter, int line_count)
{
	ft_putstr_fd("heredoc: warning: here-document at line ", 2);
	ft_putnbr_fd(line_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	g_main.is_cmd_running = FALSE;
	g_main.status = 0;
	return (NULL);
}

char	*save_heredoc(char *delim, char *heredoc)
{
	int		fd;
	char	*tmp;
	char	*name;

	name = heredoc_files(NAME);
	tmp = expand_var_heredoc(ft_strdup(heredoc));
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, tmp, ft_strlen(tmp) - ft_strlen(delim) - 1);
	close(fd);
	ft_safe_free((void **)&tmp);
	return (name);
}
