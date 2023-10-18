/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/18 16:38:15 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = get_line();
		if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
			exit_builtin(line);
		else if (ft_strncmp(line, "echo ", 5) == 0)
			echo_builtin(line);
		else if (ft_strncmp(line, "pwd", 3) == 0 && ft_strlen(line) == 3)
			pwd_builtin();
		else if (ft_strncmp(line, "cd ", 3) == 0)
			cd_builtin(line);
		else
			printf("Command not found\n");
		free(line);
	}
	return (0);
}
