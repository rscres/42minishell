/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:27:46 by renato            #+#    #+#             */
/*   Updated: 2023/12/18 14:36:02 by rseelaen         ###   ########.fr       */
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

int	lexer(char **str)
{
	char	*token;
	int		expand;
	// char	*new_str;

	token = tokenizer(*str);
	expand = 1;
	while (token)
	{
		add_token(token, get_type(token));
		ft_safe_free((void **)&token);
		token = tokenizer(NULL);
		expand = 1;
	}
	// while (g_main.open_quote)
	// {
	// 	if (g_main.open_quote == 1)
	// 		heredoc("\'");
	// 	else if (g_main.open_quote == 2)
	// 		heredoc("eof");
		// new_str = readline("> ");
		// token = tokenizer(new_str);
		// while (token)
		// {
		// 	add_token(token, get_type(token), expand);
		// 	ft_safe_free((void **)token);
		// 	token = tokenizer(NULL);
		// }
		// *str = ft_strjoin(*str, "\n");
		// *str = ft_strjoin(*str, new_str);
		// ft_safe_free((void **)&new_str);
	// }
	if (g_main.open_quote)
	{
		ft_putstr_fd("Error: unclosed quotes\n", 2);
		g_main.open_quote = 0;
		clear_token_list();
		return (1);
	}
	//---move this block----
	t_token	*tmp = g_main.token_list;
	while (tmp)
	{
		tmp->name = expand_var(tmp->name);
		tmp->name = remove_quotes(tmp->name);
		tmp = tmp->next;
	}
	// tmp = g_main.token_list;
	// while (tmp)
	// {
	// 	printf("%s=>", tmp->name);
	// 	printf("%i\n", tmp->type);
	// 	tmp = tmp->next;
	// }
	create_cmd_list();
	// parse_tree(); //need to code this
	// g_main.status = exec_builtin(g_main.cmd_list->name, g_main.cmd_list->args,
	// 	g_main.cmd_list->argc);
	// clear_token_list();
	// clear_cmd_list();
	//---move this block----
	ft_safe_free((void **)&token);
	return (0);
}
