/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:40:51 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/22 20:17:48 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		&& ft_isalnum(str[end]))
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
	free(tmp);
	tmp = ft_strjoin(tmp2, str + i + name_len);
	free(tmp2);
	free(str);
	return (tmp);
}

char	*expand_var2(char *name, int i)
{
	char	*value;
	char	*var;

	if (name[i + 1] == '?')
	{
		var = ft_strdup("?");
		value = ft_itoa(g_main.status);
	}
	else
	{
		var = get_var_name((const char *)name + i);
		value = NULL;
		if (search(g_main.env_var, var))
			value = search(g_main.env_var, var)->value;
	}
	name = insert_value(name, value, ft_strlen(var) + 1, i);
	free(var);
	return (name);
}

//integrate check_qutoes() into this function

char	*expand_var(char *name)
{
	int		quote;
	int		i;

	i = -1;
	if (!ft_strchr(name, '$'))
		return (name);
	quote = 0;
	while (name[++i])
	{
		if (name[i] == '\'' || name[i] == '\"')
			quote = check_quote(quote, name[i]);
		while (name[i] && name[i] != '\'' && quote == 1)
			i++;
		if (name[i] == '$' && name[i + 1] && name[i + 1] != '\"'
			&& name[i + 1] != ' ')
			name = expand_var2(name, i);
	}
	return (name);
}
