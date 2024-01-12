/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:49:39 by rseelaen          #+#    #+#             */
/*   Updated: 2023/12/18 15:14:40 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_argc(t_token *tmp)
{
	int		i;

	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && tmp->prev->type != INFILE
			&& tmp->prev->type != OUTFILE && tmp->prev->type != APPEND
			&& tmp->prev->type != HEREDOC)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	create_arg_list(t_cmd *cmd, t_token *tmp)
{
	cmd->args = ft_calloc(sizeof(char *), (get_argc(tmp) + 2));
	if (get_argc(tmp) > 0)
		cmd->args[cmd->argc++] = ft_strdup(tmp->prev->name);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && tmp->prev->type != INFILE
			&& tmp->prev->type != OUTFILE && tmp->prev->type != APPEND
			&& tmp->prev->type != HEREDOC)
		{
			cmd->args[cmd->argc] = ft_strdup(tmp->name);
			cmd->argc++;
		}
		tmp = tmp->next;
	}
	cmd->args[cmd->argc] = NULL;
}

void	create_cmd_list(void)
{
	t_token	*tmp;
	t_cmd	*cmd;
	int		cmd_count;

	tmp = g_main.token_list;
	cmd_count = 0;
	while (tmp)
	{
		if (tmp->type == WORD && !cmd_count)
		{
			cmd_count = 1;
			cmd = new_cmd(tmp->name, tmp->type);
			tmp = tmp->next;
			create_arg_list(cmd, tmp);
			add_cmd(cmd);
		}
		else if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			cmd = new_cmd(tmp->name, tmp->type);
			tmp = tmp->next;
			cmd->args = malloc(sizeof(char *) * 2);
			cmd->args[0] = ft_strdup(tmp->name);
			cmd->args[1] = NULL;
			cmd->argc++;
			add_cmd(cmd);
			tmp = tmp->next;
		}
		else if (tmp->type == PIPE)
		{
			cmd_count = 0;
			add_cmd(new_cmd(tmp->name, tmp->type));
			g_main.cmd_info->pipe_count += 1;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	// print_cmd_list();
}
