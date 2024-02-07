/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:49:39 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/07 17:03:07 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	create_arg_list(t_cmd *cmd, t_token *tmp_tok)
{
	cmd->args = ft_calloc((get_argc(tmp_tok) + 2), sizeof(char *));
	cmd->args[cmd->argc] = ft_strdup(tmp_tok->name);
	cmd->argc++;
	tmp_tok = tmp_tok->next;
	while (tmp_tok && tmp_tok->type != PIPE)
	{
		if (tmp_tok && ft_strcmp(tmp_tok->name, "") == 0)
		{
			tmp_tok = tmp_tok->next;
			continue ;
		}
		if (tmp_tok->type == WORD && tmp_tok->prev
			&& tmp_tok->prev->type != INFILE && tmp_tok->prev->type != OUTFILE
			&& tmp_tok->prev->type != APPEND && tmp_tok->prev->type != HEREDOC)
		{
			cmd->args[cmd->argc] = ft_strdup(tmp_tok->name);
			cmd->argc++;
		}
		tmp_tok = tmp_tok->next;
	}
	cmd->args[cmd->argc] = NULL;
}

void	create_redir(t_cmd **cmd, t_token **tmp_tok)
{
	*cmd = new_cmd((*tmp_tok)->name, (*tmp_tok)->type);
	*tmp_tok = (*tmp_tok)->next;
	(*cmd)->args = malloc(sizeof(char *) * 2);
	(*cmd)->args[0] = ft_strdup((*tmp_tok)->name);
	(*cmd)->args[1] = NULL;
	(*cmd)->argc++;
	add_cmd(*cmd);
	*tmp_tok = (*tmp_tok)->next;
}

void	create_pipe(t_cmd **cmd, t_token **tmp_tok, int *cmd_count)
{
	*cmd_count = 0;
	*cmd = new_cmd((*tmp_tok)->name, (*tmp_tok)->type);
	add_cmd(*cmd);
	*tmp_tok = (*tmp_tok)->next;
}

void	create_cmd(t_cmd **cmd, t_token **tmp_tok, int *cmd_count)
{
	*cmd_count = 1;
	*cmd = new_cmd((*tmp_tok)->name, (*tmp_tok)->type);
	create_arg_list(*cmd, *tmp_tok);
	add_cmd(*cmd);
}

void	create_cmd_list(void)
{
	t_token	*tmp_tok;
	t_cmd	*cmd;
	int		cmd_count;

	tmp_tok = g_main.token_list;
	cmd_count = 0;
	while (tmp_tok)
	{
		if (tmp_tok && ft_strcmp(tmp_tok->name, "") == 0)
		{
			tmp_tok = tmp_tok->next;
			continue ;
		}
		if (tmp_tok->type == WORD && !cmd_count)
			create_cmd(&cmd, &tmp_tok, &cmd_count);
		else if (tmp_tok->type == INFILE || tmp_tok->type == OUTFILE
			|| tmp_tok->type == APPEND || tmp_tok->type == HEREDOC)
			create_redir(&cmd, &tmp_tok);
		else if (tmp_tok->type == PIPE)
			create_pipe(&cmd, &tmp_tok, &cmd_count);
		else
			tmp_tok = tmp_tok->next;
	}
}
