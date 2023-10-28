/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 20:39:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/27 21:23:11 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

typedef struct s_token
{
	struct s_src	*src;
	int				text_len;
	char			*text;
}	t_token;

t_token	*tokenize(t_token *src);
void	free_token(t_token *tok);

#endif //SCANNER_H