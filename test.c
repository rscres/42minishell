/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:46:32 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/21 14:53:25 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

int	main(void)
{
	char	*str;
	char	**split;
	int		i;

	str = "hello=123 A-";
	split = ft_split(str, '=');
	i = 0;
	while (split[i])
	{
		printf("split[%d] = %s\n", i, split[i]);
		i++;
	}
	return (0);
}