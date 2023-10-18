/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/18 13:54:37 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_line(void)
{
	char	*line;

	line = readline("my_shell$ ");
	if (strlen(line) > 0)
		add_history(line);
	return (line);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = get_line();
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(0);
		}
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
