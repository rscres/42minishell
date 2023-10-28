/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:14:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/26 20:12:43 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(void)
{
	char	*line;
	t_cmd	*cmd;

	sig_init();
	while (1)
	{
		line = get_line(1);
		cmd = parser(line);
		while (cmd)
		{
			printf("cmd->cmd: %s\n", cmd->name);
			printf("cmd->args->value: %s\n", cmd->args->value);
			cmd = cmd->next;
		}
		if (line)
			free(line);
	}
	return (0);
}
