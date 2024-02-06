/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:33:46 by renato            #+#    #+#             */
/*   Updated: 2024/02/05 22:35:28 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ig_check_pipe(t_token *token)
{
	while (token->next)
		token = token->next;
	if (token->type == PIPE && token->prev)
		return (1);
	return (0);
}

void	ig_check_open(char *token, char **str)
{
	int		quote;
	char	*new_str;

	while (g_main.open_quote || ig_check_pipe(g_main.token_list))
	{
		quote = g_main.open_quote;
		new_str = readline("> ");
		token = tokenizer(new_str);
		while (token)
		{
			add_token(token, get_type(token));
			ft_safe_free((void **)&token);
			token = tokenizer(NULL);
		}
		if (quote)
			*str = ft_strjoin_free(*str, "\n");
		else
			*str = ft_strjoin_free(*str, " ");
		*str = ft_strjoin_free(*str, new_str);
		ft_safe_free((void **)&new_str);
	}
}
