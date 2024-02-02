/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:40:51 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/01 14:51:00 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//The functions in this file are used to expand the variables in the command
// line. For example, if the user types "echo $USER", the program will print
// "echo rseelaen".

static char	*remove_dollar(char	*var)
{
	char	*tmp;

	tmp = ft_strtrim(var, "$");
	free(var);
	return (tmp);
}

static char	*get_var_name(const char *str)
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
		&& ft_isalnum(str[end])) //change to is_valid_var_char
		end++;
	if (start != end)
		var = ft_strndup((str + start), end - start);
	var = remove_dollar(var);
	return (var);
}

//maybe change ft_strjoin so it doens't need outside free()'s

static char	*insert_value(char *str, char *value, int name_len, int pos)
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

char	*expand_var2(char *str, int *i)
{
	char	*value;
	char	*var;
	int		empty;

	empty = 0;
	if (str[*i + 1] == '?')
	{
		var = ft_strdup("?");
		value = ft_itoa(g_main.status);
	}
	else
	{
		var = get_var_name((const char *)str + *i);
		if (search(g_main.env_var, var))
			value = ft_strdup(search(g_main.env_var, var)->value);
		else
		{
			value = ft_strdup("");
			empty = 1;
		}
	}
	str = insert_value(str, value, ft_strlen(var) + 1, *i);
	if (empty == 0)
		*i = *i + ft_strlen(value) - 1;
	else
		*i = ft_strlen(str) - ft_strlen(var) - 1;
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
		while (str[i] && str[i] != '\'' && quote == 1)
			i++;
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '\"'
			&& str[i + 1] != ' ')
			str = expand_var2(str, &i);
	}
	return (str);
}
