/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:49:39 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/01 14:41:04 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	get_argc(t_token *tmp)
{
	int		i;

	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && tmp->prev && tmp->prev->type != INFILE
			&& tmp->prev->type != OUTFILE && tmp->prev->type != APPEND
			&& tmp->prev->type != HEREDOC)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	create_arg_list(t_cmd *cmd, t_token *tmp_tok)
{
	cmd->args = malloc(sizeof(char *) * (get_argc(tmp_tok) + 2));
	cmd->args[cmd->argc] = ft_strdup(tmp_tok->name);
	cmd->argc++;
	tmp_tok = tmp_tok->next;
	while (tmp_tok && tmp->type != PIPE)
	{
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
		{
			cmd_count = 1;
			cmd = new_cmd(tmp_tok->name, tmp_tok->type);
			create_arg_list(cmd, tmp_tok);
			add_cmd(cmd);
		}
		else if (tmp_tok->type == INFILE || tmp_tok->type == OUTFILE
			|| tmp_tok->type == APPEND || tmp_tok->type == HEREDOC)
		{
			cmd = new_cmd(tmp_tok->name, tmp_tok->type);
			tmp_tok = tmp_tok->next;
			cmd->args = malloc(sizeof(char *) * 2);
			cmd->args[0] = ft_strdup(tmp_tok->name);
			cmd->args[1] = NULL;
			cmd->argc++;
			add_cmd(cmd);
			tmp_tok = tmp_tok->next;
		}
		else if (tmp_tok->type == PIPE)
		{
			cmd_count = 0;
			add_cmd(new_cmd(tmp_tok->name, tmp_tok->type));
			g_main.pipe->pipe_counter += 1;
			tmp_tok = tmp_tok->next;
		}
		else
			tmp_tok = tmp_tok->next;
	}
}
