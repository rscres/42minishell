/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:09 by igenial           #+#    #+#             */
/*   Updated: 2024/01/09 11:20:13 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void ft_first_born(t_cmd *cmd);

void ft_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	if (cmd->prev->type == WORD)
		tmp = cmd->prev;
	tmp = cmd->next;
	ft_first_born(tmp);
	// estamos com o cmd na posição 0
}
void ft_first_born(t_cmd *cmd)
{
	int		linked[2];
//	int		file;
	pid_t	pid;

	if(pipe(linked) == -1)
		exit(FALSE);
	pid = fork();
	if (pid == 0)
	{
		close(linked[0]);
//		dup2(link[1], 1); antes de exec
//		close(link[1]); antes de exec
		//check_Path
		if (check_if_builtin(cmd->name))
		g_main.status = exec_builtin(cmd->name, cmd->args, cmd->argc);

	}
	close(linked[1]);
	wait(&g_main.status);
}

int ft_creat_child(void)
{
	if(g_main.cmd_info->pipe_count == )
		ft_first_born();
	if(g_main.cmd_info->pipe_count == 2)
		ft_sec_born();
	if(g_main.cmd_info->pipe_count >  3)
		ft_last_born();
}


