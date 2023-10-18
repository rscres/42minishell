/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:30:43 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/18 15:31:01 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_line(void)
{
	char	*line;

	line = readline("my_shell$> ");
	if (strlen(line) > 0)
		add_history(line);
	return (line);
}