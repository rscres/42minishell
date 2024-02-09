/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:40:51 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/07 21:34:50 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*expand_var2(char *str, int *i)
{
	char	*value;
	char	*var;

	if (str[*i + 1] == '?')
	{
		var = ft_strdup("?");
		value = ft_itoa(adjust_status(g_main.status));
	}
	else
	{
		var = get_var_name((const char *)str + *i);
		if (search(g_main.env_var, var))
			value = ft_strdup(search(g_main.env_var, var)->value);
		else
			value = ft_strdup("");
	}
	str = insert_value(str, value, ft_strlen(var) + 1, *i);
	*i = *i + ft_strlen(value) - 1;
	if (*i == 0)
		*i = -1;
	ft_safe_free((void **)&var);
	ft_safe_free((void **)&value);
	return (str);
}

char	*expand_var(char *str)
{
	int		quote;
	int		i;

	if (!ft_strchr(str, '$'))
		return (str);
	i = -1;
	quote = 0;
	while ((size_t)++i < ft_strlen(str) && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = check_quote(quote, str[i]);
		if (!close_single_quote(str, &i, &quote))
			continue ;
		if (str[i] == '$' && str[i + 1] == '\"')
			continue ;
		if (str[i] == '$')
			str = expand_var2(str, &i);
	}
	return (str);
}
