/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:30:25 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/23 18:58:24 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exit_builtin(char *line)
{
	if (line)
		free(line);
	exit(0);
}

void	echo_builtin(char *line)
{
	char	*tmp;

	// tmp = line;
	tmp = ft_strtrim(line, " ");
	if (ft_strncmp(tmp, "-n", 2) == 0 && ft_strlen(tmp) > 2)
	{
		free(tmp);
		tmp = ft_strtrim(line + 3, " ");
		printf("%s%%\n", tmp);
	}
	else if (ft_strncmp(tmp, "-n", 2) == 0 && tmp[2] == '\0')
	{
		free(tmp);
		return ;
	}
	else
	{
		if (check_closed_quotes(line))
		{
			ft_strtrim(tmp, "\"");
			ft_strtrim(tmp, "\'");
		}
		printf("%s\n", tmp);
	}
	if (tmp)
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
