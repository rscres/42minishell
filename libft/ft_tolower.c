/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:59:35 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/27 13:02:41 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ft_tolower() converts the letter c to lower case, if possible.
int	ft_tolower(int a)
{
	if (a >= 65 && a <= 90)
		return (a + 32);
	return (a);
}
