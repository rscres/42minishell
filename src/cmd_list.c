/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:49:39 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/21 17:24:07 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd	*new_cmd(char *name)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(name);
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (g_main.cmd_list == NULL)
	{
		g_main.cmd_list = cmd;
		return ;
	}
	tmp = g_main.cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

// void	clear_cmd_list(void)
// {
// 	t_cmd	*tmp;

// 	while (g_main.cmd_list)
// 	{
// 		tmp = g_main.cmd_list;
// 		g_main.cmd_list = g_main.cmd_list->next;
// 		free(tmp->name);
// 		free(tmp);
// 	}
// }

//------------------TEST FUNCTIONS------------------//
//------------------TEST FUNCTIONS------------------//
void	print_cmd_list(void)
{
	t_cmd	*tmp;
	int		i;

	tmp = g_main.cmd_list;
	while (tmp)
	{
		printf("cmd = %s\n", tmp->name);
		i = 0;
		while (i < tmp->argc)
		{
			printf("arg[%i] = %s\n", i, tmp->args[i]);
			i++;
		}
		printf("argc = %i\n", tmp->argc);
		tmp = tmp->next;
	}
}
//------------------TEST FUNCTIONS------------------//
//------------------TEST FUNCTIONS------------------//

void	clear_cmd_list(void)
{
	t_cmd	*tmp;
	int		i;

	while (g_main.cmd_list)
	{
		tmp = g_main.cmd_list;
		g_main.cmd_list = g_main.cmd_list->next;
		i = 0;
		while (i < tmp->argc)
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		free(tmp->name);
		free(tmp);
	}
}

void	create_cmd_list(void)
{
	t_token	*tmp;
	t_cmd	*cmd;
	t_token	*hold;
	int		i;

	tmp = g_main.token_list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			cmd = new_cmd(tmp->name);
			tmp = tmp->next;
			hold = tmp;
			i = 0;
			while (tmp && tmp->type == WORD)
			{
				i++;
				tmp = tmp->next;
			}
			cmd->args = malloc(sizeof(char *) * (i + 1));
			tmp = hold;
			while (tmp && tmp->type == WORD)
			{
				cmd->args[cmd->argc] = ft_strdup(tmp->name);
				cmd->argc++;
				tmp = tmp->next;
			}
			cmd->args[cmd->argc] = NULL;
			add_cmd(cmd);
		}
		else if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			cmd = new_cmd(tmp->name);
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
			add_cmd(new_cmd(tmp->name));
			tmp = tmp->next;
		}
	}
	// print_cmd_list();
}
