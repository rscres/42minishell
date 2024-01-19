/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:20:54 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/19 00:03:01 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	remove_heredoc(int last)
{
	char	*cur_file;
	char	*num;
	char	*tmp;
	int		i;
	int		fd;

	i = 0;
	while (i <= last)
	{
		num = ft_itoa(i);
		while (ft_strlen(num) < 3)
		{
			tmp = ft_strjoin("0", num);
			ft_safe_free((void **)&num);
			num = tmp;
		}
		cur_file = ft_strjoin("heredoc", num);
		ft_safe_free((void **)&num);
		fd = open(cur_file, O_RDONLY);
		if (fd != -1)
			unlink(cur_file);
		ft_safe_free((void **)&cur_file);
		i++;
	}
	return (0);
}