/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:16:12 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/27 21:17:25 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H

# include "../libft/libft.h"

# define EOF -1
# define INIT_SRC_POS 0

typedef struct s_src
{
	char	*line;
	long	len;
	long	pos;
}	t_src;

char	next_char(t_src *src);
void	unget_char(t_src *src);
char	peek_char(t_src *src);
void	skip_white_spaces(t_src *src);

#endif //SOURCE_H
