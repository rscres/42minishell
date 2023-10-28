/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:49:49 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/24 11:34:03 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H

# define EOF -1
# define ERRCHAR 0

# define INIT_SRC_POS -2

typedef struct s_source
{
	char	*buffer;       /* the input text */
	long	bufsize;       /* size of the input text */
	long	curpos;       /* absolute char position in source */
}	t_source;

char	next_char(t_source *src);
void	unget_char(t_source *src);
char	peek_char(t_source *src);
void	skip_white_spaces(t_source *src);

#endif //SOURCE_H