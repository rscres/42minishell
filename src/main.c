/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:19 by rseelaen          #+#    #+#             */
/*   Updated: 2023/11/03 15:46:04 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// char	*get_line(int flag)
// {
// 	char	*line;

// 	if (flag == 1)
// 		line = readline("> ");
// 	else
// 		line = readline("minishell$ ");
// 	if (line)
// 		add_history(line);
// 	return (line);
// }

char	*get_line(void)
{
	char	*line;

	line = readline("msh$ ");
	if (!line)
		return (NULL);
	while (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\\')
	{
		line[ft_strlen(line) - 1] = '\0';
		line = ft_strjoin(line, readline("> "));
	}
	if (line)
		add_history(line);
	return (line);
}

int	exec(t_token **tokens)
{
	if (ft_strncmp(line, "echo", 4) == 0)
		printf("%s\n", line + 5);
	return (0);
}

int	main(void)
{
	char	*line;
	t_main	data;

	signal_set();
	get_env(data.env_var);
	print_hashtable(data.env_var);
	while (1)
	{
		line = get_line();
		if (!line)
		{
			printf("exit");
			exit(0);
		}
		data.tokens = parse_line(line);
		exec(line);
		if (line)
			free(line);
	}
	return (0);
}
