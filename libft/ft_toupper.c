/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:57:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/27 13:02:48 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ft_toupper() converts the letter c to upper case, if possible.
int	ft_toupper(int a)
{
	if (a >= 97 && a <= 122)
		return (a - 32);
	return (a);
}
