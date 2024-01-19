/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:20:54 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/19 16:45:44 by rseelaen         ###   ########.fr       */
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
