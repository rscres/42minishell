/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:18:54 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/27 21:27:59 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "source.h"

char	next_char(t_src *src)
{
	if (!src || !src->line[src->pos])
		return (0);
	if (++src->pos >= src->len)
	{
		src->pos = src->len;
		return (EOF);
	}
	return (src->line[src->pos]);
}

void	unget_char(t_src *src)
{
	if (!src || src->pos > 0)
		return ;
	src->pos--;
}

char	peek_char(t_src *src)
{
	if (!src || !src->line[src->pos])
		return (0);
	if (src->pos >= src->len)
		return (EOF);
	return (src->line[src->pos + 1]);
}

void	skip_white_spaces(t_src *src)
{
	if (!src || !src->line[src->pos])
		return ;
	while (src->line[src->pos + 1] != EOF
		&& ft_iswhitespace(src->line[src->pos]))
		src->pos++;
}
