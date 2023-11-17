/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:40:51 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/17 17:19:38 by renato           ###   ########.fr       */
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
	end = start;
	while (str[end] && !ft_iswhitespace(str[end]))
		end++;
	if (start != end)
		var = ft_strndup((str + start), end - start);
	var = remove_dollar(var);
	return (var);
}

//maybe change ft_strjoin so it doens't need outside free()'s

char	*insert_value(char *str, char *value, int name_len)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	while (str[i] != '$')
		i++;
	tmp = ft_strndup(str, i);
	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	tmp = ft_strjoin(tmp2, str + i + name_len);
	free(tmp2);
	free(str);
	return(tmp);

}

void	expand_var(char **args)
{
	char	*value;
	char	*var;
	int		i;

	i = 0;
	value = NULL;
	while (args[i])
	{
		if (ft_strchr(args[i], '$'))
		{
			var = get_var_name((const char *)args[i]);
			value = getenv(var);
			args[i] = insert_value(args[i], value, ft_strlen(var) + 1);
			free(var);
		}
		i++;
	}
}
