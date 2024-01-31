/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:27:46 by renato            #+#    #+#             */
/*   Updated: 2024/01/31 16:37:42 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_type(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(str, ">"))
		return (OUTFILE);
	else if (!ft_strcmp(str, "<"))
		return (INFILE);
	else if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (WORD);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		quote;
	char	*tmp;

	i = 0;
	j = 0;
	quote = 0;
	tmp = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = check_quote(quote, str[i]);
		if ((str[i] == '\'' || str[i] == '\"')
			&& check_quote(quote, str[i]) != quote)
			i++;
		else
			tmp[j++] = str[i++];
	}
	ft_safe_free((void **)&str);
	return (tmp);
}

int	syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\'", 2);
	clear_token_list();
	g_main.status = 2;
	return (1);
}

static int	check_syntax(void)
{
	t_token	*tmp;

	tmp = g_main.token_list;
	while (tmp)
	{
		if (tmp->type == APPEND || tmp->type == HEREDOC
			|| tmp->type == OUTFILE || tmp->type == INFILE)
		{
			if (!tmp->next || tmp->next->type != WORD)
				return (syntax_error(tmp->name));
		}
		if (tmp->type == PIPE && (tmp->prev == NULL
				|| (tmp->next && tmp->next->type == PIPE)))
			return (syntax_error(tmp->name));
		tmp = tmp->next;
	}
	return (0);
}

int	check_and_clear(void)
{
	t_token	*tmp;

	tmp = g_main.token_list;
	while (tmp)
	{
		tmp->name = expand_var(tmp->name);
		tmp->name = remove_quotes(tmp->name);
		tmp = tmp->next;
	}
	if (g_main.token_list && check_syntax())
	{
		g_main.status = 2;
		return (2);
	}
	return (0);
}

int	lexer(char **str)
{
	char	*token;
	char	*new_str;

	token = tokenizer(*str);
	while (token)
	{
		add_token(token, get_type(token));
		ft_safe_free((void **)&token);
		token = tokenizer(NULL);
	}
	while (g_main.open_quote)
	{
		new_str = readline("> ");
		token = tokenizer(new_str);
		while (token)
		{
			add_token(token, get_type(token));
			ft_safe_free((void **)&token);
			token = tokenizer(NULL);
		}
		*str = ft_strjoin_free(*str, "\n");
		*str = ft_strjoin_free(*str, new_str);
		ft_safe_free((void **)&new_str);
	}
	g_main.line = *str;
	if (g_main.open_quote)
	{
		ft_putstr_fd("Error: unclosed quotes\n", 2);
		g_main.open_quote = 0;
		clear_token_list();
		g_main.status = 1;
		return (1);
	}
	if (check_and_clear())
		return (1);
	create_cmd_list();
	clear_token_list();
	ft_safe_free((void **)&token);
	return (0);
}
