/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:04:44 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/09 13:54:59 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*append_to_heredoc(char *heredoc, char *line)
{
	heredoc = ft_strjoin_free(heredoc, line);
	heredoc = ft_strjoin_free(heredoc, "\n");
	return (heredoc);
}

static char	*heredoc_loop(char *delim, char *heredoc)
{
	int		line_count;
	char	*line;

	line_count = 0;
	signal(SIGINT, heredoc_signal);
	while (1)
	{
		line_count++;
		line = readline("> ");
		if (!line)
		{
			heredoc = append_to_heredoc(heredoc, delim);
			if (g_main.signal_received == FALSE)
				heredoc_error(delim, line_count);
			break ;
		}
		heredoc = append_to_heredoc(heredoc, line);
		if (!ft_strcmp(line, delim))
			break ;
		ft_safe_free((void **)&line);
	}
	signal(SIGINT, sigint);
	g_main.signal_received = FALSE;
	return (heredoc);
}

static void	child_heredoc(int pipefd[2], char *delimiter)
{
	char	*heredoc;

	close(pipefd[0]);
	heredoc = ft_strdup("");
	heredoc = heredoc_loop(delimiter, heredoc);
	if (!heredoc)
		heredoc_exit(EXIT_FAILURE);
	write(pipefd[1], heredoc, strlen(heredoc) + 1);
	close(pipefd[1]);
	free(heredoc);
	heredoc_exit(EXIT_SUCCESS);
}

static char	*parent_heredoc(int pipefd[2], pid_t pid, char *delimiter)
{
	char	*name;
	char	buffer[4096];
	char	*heredoc;

	close(pipefd[1]);
	wait(&pid);
	read(pipefd[0], buffer, sizeof(buffer));
	heredoc = strdup(buffer);
	close(pipefd[0]);
	name = save_heredoc(delimiter, heredoc);
	g_main.line = ft_strjoin_free(g_main.line, "\n");
	g_main.line = ft_strjoin_free(g_main.line, heredoc);
	ft_safe_free((void **)&heredoc);
	g_main.is_cmd_running = FALSE;
	g_main.status = 0;
	return (name);
}

char	*heredoc(char *delimiter)
{
	char	*name;
	int		pipefd[2];
	pid_t	pid;

	name = NULL;
	signal(SIGINT, SIG_IGN);
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_heredoc(pipefd, delimiter);
	else
		name = parent_heredoc(pipefd, pid, delimiter);
	signal(SIGINT, sigint);
	return (name);
}
