/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:16:06 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/28 15:18:21 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_safe_free((void **)&tab[i++]);
	ft_safe_free((void **)tab);
	return (i);
}
