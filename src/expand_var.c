/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:40:51 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/16 18:36:13 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	expand_var(char **args)
{
	char	*tmp;

	while (args)
	{
		if (ft_strchr(args, '$'))
		{
			tmp = ft_strdup(args);
			free(args);
			args = ft_split(tmp, '$');
			free(tmp);
		}
		else
			break ;
	}
}
