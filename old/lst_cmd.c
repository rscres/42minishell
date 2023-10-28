/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:24:57 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/26 20:28:33 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd	*cmdlst_new(int content)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->name = content;
	node->herodoc = 0;
	node->infile = 0;
	node->outfile = 0;
	node->args = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	cmdlst_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

// void	cmdlst_clear(t_cmd **lst)
// {
// 	t_cmd	*current;
// 	t_cmd	*next;

// 	current = *lst;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->name);
// 		arglst_clear(&current->args);
// 		free(current);
// 		current = next;
// 	}
// 	*lst = NULL;
// }
