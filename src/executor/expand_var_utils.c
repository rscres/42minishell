/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:33:54 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/07 21:34:41 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*remove_dollar(char	*var)
{
	char	*tmp;

	tmp = ft_strtrim(var, "$");
	free(var);
	return (tmp);
}

char	*get_var_name(const char *str)
{
	char	*var;
	int		start;
	int		end;

	start = 0;
	var = NULL;
	while (str[start] != '$')
		start++;
	end = start + 1;
	while (str[end] && !ft_iswhitespace(str[end]) && str[end] != '$'
		&& (isalnum(str[end]) || str[end] == '_'))
		end++;
	if (start != end)
		var = ft_strndup((str + start), end - start);
	var = remove_dollar(var);
	return (var);
}

char	*insert_value(char *str, char *value, int name_len, int pos)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if (!value)
		value = "";
	i = pos;
	tmp = NULL;
	while (str[i] != '$')
		i++;
	tmp = ft_strndup(str, i);
	tmp2 = ft_strjoin(tmp, value);
	ft_safe_free((void **)&tmp);
	tmp = ft_strjoin(tmp2, str + i + name_len);
	ft_safe_free((void **)&tmp2);
	ft_safe_free((void **)&str);
	return (tmp);
}

int	close_single_quote(char *str, int *i, int *quote)
{
	while (str[*i] && *quote == 1)
	{
		(*i)++;
		if (str[*i] == '\'')
		{
			*quote = 0;
			return (0);
		}
	}
	return (1);
}
