/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:20:54 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/18 19:35:38 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*name_heredoc(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	name = ft_strndup(str, i);
	return (name);
}