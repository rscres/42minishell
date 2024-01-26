/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:04:44 by rseelaen          #+#    #+#             */
/*   Updated: 2024/01/25 17:33:27 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*expand_var_heredoc(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			str = expand_var2(str, i);
	}
	return (str);
}

static char	*heredoc_error(char *delimiter, int line_count)
{
	ft_putstr_fd("heredoc: warning: here-document at line ", 2);
	ft_putnbr_fd(line_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	g_main.is_cmd_running = 0;
	g_main.status = 0;
	return (NULL);
}

static char	*save_heredoc(char *delim, char *heredoc)
{
	int		fd;
	char	*tmp;
	char	*name;

	name = heredoc_files(NAME);
	tmp = expand_var_heredoc(ft_strdup(heredoc));
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, tmp, ft_strlen(tmp) - ft_strlen(delim) - 1);
	close(fd);
	ft_safe_free((void **)&tmp);
	return (name);
}

void		heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		(void)signal;
		g_main.signal_received = TRUE;
		g_main.status = 130;
		// ft_putendl_fd("", 1);
		close(0);
		// rl_replace_line("", 0);
	}
}

// #include <termios.h>

// static char *heredoc_loop(char *delim, char *heredoc) {
//     int line_count;
//     char *line;
//     struct termios old_term, new_term;

//     line_count = 0;
//     rl_catch_signals = 1;
//     signal(SIGINT, heredoc_signal);

//     // Save the original terminal settings
//     tcgetattr(STDIN_FILENO, &old_term);

//     // Set the terminal to non-blocking mode
//     new_term = old_term;
//     new_term.c_cc[VMIN] = 0;
//     new_term.c_cc[VTIME] = 0;
//     tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

//     while (1 && ++line_count && g_main.signal_received == FALSE) {
//         line = readline("> ");
//         if (!line) {
//             heredoc = ft_strjoin_free(heredoc, delim);
//             heredoc = ft_strjoin_free(heredoc, "\n");
//             heredoc_error(delim, line_count);
//             break;
//         }
//         heredoc = ft_strjoin_free(heredoc, line);
//         heredoc = ft_strjoin_free(heredoc, "\n");
//         if (!ft_strcmp(line, delim))
//             break;
//         ft_safe_free((void **)&line);
//     }

//     // Restore the original terminal settings
//     tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

//     signal(SIGINT, handler);
//     g_main.signal_received = FALSE;
//     rl_catch_signals = 1;
//     return (heredoc);
// }

// static char	*heredoc_loop(char *delim, char *heredoc)
// {
// 	int		line_count;
// 	char	*line;

// 	line_count = 0;
// 	rl_catch_signals = 0;
// 	signal(SIGINT, heredoc_signal);
// 	while (1 && ++line_count && g_main.signal_received == FALSE)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			heredoc = ft_strjoin_free(heredoc, delim);
// 			heredoc = ft_strjoin_free(heredoc, "\n");
// 			heredoc_error(delim, line_count);
// 			break ;
// 		}
// 		heredoc = ft_strjoin_free(heredoc, line);
// 		heredoc = ft_strjoin_free(heredoc, "\n");
// 		if (!ft_strcmp(line, delim))
// 			break ;
// 		ft_safe_free((void **)&line);
// 	}
// 	signal(SIGINT, handler);
// 	g_main.signal_received = FALSE;
// 	rl_catch_signals = 1;
// 	return (heredoc);
// }

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
			heredoc = ft_strjoin_free(heredoc, delim);
			heredoc = ft_strjoin_free(heredoc, "\n");
			if (g_main.signal_received == FALSE)
				heredoc_error(delim, line_count);
			break ;
		}
		heredoc = ft_strjoin_free(heredoc, line);
		heredoc = ft_strjoin_free(heredoc, "\n");
		if (!ft_strcmp(line, delim))
			break ;
		ft_safe_free((void **)&line);
	}
	signal(SIGINT, handler);
	g_main.signal_received = FALSE;
	return (heredoc);
}

// char	*heredoc(char *delimiter)
// {
// 	char	*heredoc;
// 	char	*name;

// 	g_main.is_cmd_running = 1;
// 	heredoc = ft_strdup("");
// 	heredoc = heredoc_loop(delimiter, heredoc);
// 	if (!heredoc)
// 		return (NULL);
// 	name = save_heredoc(delimiter, heredoc);
// 	g_main.line = ft_strjoin_free(g_main.line, "\n");
// 	g_main.line = ft_strjoin_free(g_main.line, heredoc);
// 	ft_safe_free((void **)&heredoc);
// 	g_main.is_cmd_running = 0;
// 	g_main.status = 0;
// 	return (name);
// }

char	*heredoc(char *delimiter)
{
    char	*heredoc;
    char	*name;
    // pid_t	pid;

    // pid = fork();
	// name = NULL;
    // if (pid < 0)
    // {
    //     perror("fork failed");
    //     exit(EXIT_FAILURE);
    // }
    // g_main.is_cmd_running = 1;
	// heredoc = ft_strdup("");
    // if (pid == 0)
    // {
    //     // This is the child process
    //     heredoc = heredoc_loop(delimiter, heredoc);
	// 	// printf("heredoc : %s\n", heredoc);
    //     if (!heredoc)
    //         exit(EXIT_FAILURE);
    //     exit(EXIT_SUCCESS);
    // }
    // else
    // {
    //     // This is the parent process
    //     // Wait for the child process to finish
    //     wait(NULL);
    // }
	int pipefd[2];

	if (pipe(pipefd) == -1) {
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid < 0) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		// This is the child process
		close(pipefd[0]); // Close unused read end
		heredoc = heredoc_loop(delimiter, heredoc);
		if (!heredoc)
			exit(EXIT_FAILURE);
		write(pipefd[1], heredoc, strlen(heredoc) + 1); // Write heredoc to pipe
		close(pipefd[1]); // Close write end
		exit(EXIT_SUCCESS);
	} else {
		// This is the parent process
		close(pipefd[1]); // Close unused write end
		char buffer[4096];
		read(pipefd[0], buffer, sizeof(buffer)); // Read heredoc from pipe
		heredoc = strdup(buffer);
		close(pipefd[0]); // Close read end
		wait(NULL); // Wait for the child process to finish
	}
	name = save_heredoc(delimiter, heredoc);
	printf("name : %s\n", name);
	printf("heredoc : %s\n", heredoc);
	g_main.line = ft_strjoin_free(g_main.line, "\n");
	g_main.line = ft_strjoin_free(g_main.line, heredoc);
	ft_safe_free((void **)&heredoc);
	g_main.is_cmd_running = 0;
	g_main.status = 0;
    return (name);
}
