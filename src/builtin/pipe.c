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

}
void ft_first_born(t_cmd *cmd)
{
	int		linked[2];
	pid_t	pid;

	if(pipe(linked) == -1)
		exit(FALSE);
	pid = fork();
	if (pid == 0)
	{
		close(linked[0]);
		dup2(linked[1], 1);
		close(linked[1]);
	}
	else
	{
		close(linked[0]);
		close(linked[1]);
		wait(&g_main.status);
	}
}



