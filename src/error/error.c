/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:18:39 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/01 15:18:39 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// void	ft_error(char *str, int err)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putendl_fd(strerror(errno), 2);
// 	g_main.status = err;
// }

int	ft_error(char *str, char *msg, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	g_main.status = err;
	return (err);
}