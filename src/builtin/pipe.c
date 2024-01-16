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

void ig_first_born(t_cmd *cmd, int *fd);
void ig_second_born(t_cmd *cmd, int *fd);
void ig_open_linked(void);

void ig_pipe(t_cmd *cmd)
{
	int fd[2];
	if (check_if_builtin(cmd->name)) {
		g_main.status = exec_builtin(cmd->name, cmd->args, cmd->argc);
	}
	else
	{
		g_main.pipe->path = check_path(cmd->name);
		if (access(cmd->name, F_OK))
		{
			write(2, "oipipe\n", 8);
			pipe(fd);
			ig_first_born(cmd, fd);
			cmd = cmd->next;
			while (cmd->type != WORD)
				cmd = cmd->next;
			g_main.pipe->path = check_path(cmd->name);
			if (access(cmd->name, F_OK))
					ig_second_born(cmd, fd);
		}
		//else if (g_main.pipe->path)
			//ig_first_born(cmd);
	}
}
void ig_first_born(t_cmd *cmd, int *fd)
{
	pid_t pid;
	//char fdline[1000];

	write(2, "oi\n", 4);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(g_main.pipe->path, cmd->args, NULL);
		ft_putstr_fd("execve error\n", 2);
		exit(1);
	}
	else {
		//close(fd[0]);
		close(fd[1]);
		waitpid(pid, &g_main.status, 0);
	}
}
void ig_second_born(t_cmd *cmd, int *fd)
{
	pid_t pid;
	//char fdline[1000];
//	printf("entrei no segundo\n");

//	read(fd[0],fdline,1000);
//	printf("%s", fdline);

	pid = fork();
	if (pid == 0)
	{
		//close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
//		read(0,fdline,1000);
		printf("\n\n__recebe__\n\n");
//		printf("%s", fdline);
		execve(g_main.pipe->path, cmd->args, NULL);
		exit(1);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &g_main.status, 0);
	}

}

void ig_open_linked(void)
{
	if (pipe(g_main.pipe->linked) == -1)
		exit(FALSE);
}


