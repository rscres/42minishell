/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:30:43 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/26 12:40:10 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_line(int num)
{
	char	*line;

	if (num == 2)
		line = readline("> ");
	else
		line = readline("my_shell$ ");
	if (line && strlen(line) > 0)
		add_history(line);
	return (line);
}
