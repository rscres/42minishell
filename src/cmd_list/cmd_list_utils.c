/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:12:27 by rseelaen          #+#    #+#             */
/*   Updated: 2023/12/06 17:17:54 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd	*new_cmd(char *name, int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(name);
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->redir = 0;
	cmd->fd_in = 1;
	cmd->fd_out = 0;
	cmd->type = type;
	cmd->next = NULL;
	cmd->prev = NULL;
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
	tmp->next->prev = tmp;
}

void	clear_cmd_list(void)
{
	t_cmd	*tmp;
	int		i;

	while (g_main.cmd_list)
	{
		tmp = g_main.cmd_list;
		g_main.cmd_list = g_main.cmd_list->next;
		i = 0;
		while (tmp->args[i])
		{
			ft_safe_free((void **)&tmp->args[i]);
			i++;
		}
		ft_safe_free((void **)&tmp->args);
		ft_safe_free((void **)&tmp->name);
		ft_safe_free((void **)&tmp);
	}
}

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