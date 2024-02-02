/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:49:27 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/27 13:02:18 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ft_substr() allocates (with malloc(3)) and returns a substring from the 
//string ’s’, if within 'len'.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	char	*dest;

	slen = ft_strlen(s);
	if (!s || start >= slen)
	{
		dest = (char *)malloc(1);
		dest[0] = '\0';
		return (dest);
	}
	if (start + len > slen)
		len = slen - start;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (j < len)
		*(dest + j++) = *(s + i++);
	*(dest + j) = '\0';
	return (dest);
}
