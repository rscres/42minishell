/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:30:25 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/18 16:37:30 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exit_builtin(char *line)
{
	free(line);
	exit(0);
}

void	echo_builtin(char *line)
{
	char	*tmp;

	tmp = line + 5;
	tmp = ft_strtrim(tmp, " ");
	if (tmp[0] == '\"' && tmp[strlen(tmp) - 1] == '\"')
		ft_strtrim(tmp, "\"");
	printf("%s\n", tmp);
	free(tmp);
}

void	pwd_builtin(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

void	cd_builtin(char *line)
{
	char	*tmp;

	tmp = line + 3;
	tmp = ft_strtrim(tmp, " ");
	if (chdir(tmp) == -1)
		printf("cd: no such file or directory: %s\n", tmp);
	free(tmp);
}
