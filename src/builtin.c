/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 01:18:46 by renato            #+#    #+#             */
/*   Updated: 2023/11/15 01:42:52 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_pwd(void)
{
    char    *cwd;

    cwd = getcwd(NULL, 0);
    ft_putstr(cwd);
    ft_putchar('\n');
    free(cwd);
    return (0);
}

int ft_cd(char **args)
{
    if (!g_main.cmd_list->argc == 0)
    {
        printf("cd: HOME\n");
        if (chdir(getenv("HOME")) != 0)
            perror("cd");
    }
    else
    {
        if (chdir(args[0]) != 0)
            perror("cd");
    }
    return (0);
}

int ft_echo(char **args)
{
    int     i;
    int     n_flag;

    i = 0;
    n_flag = 0;
    while (args[i])
    {
        // printf("args[%i] = %s\n", i, args[i]);
        if (!ft_strcmp(args[i], "-n"))
        {
            n_flag = 1;
            i++;
            continue ;
        }
        ft_putstr(args[i]);
        if (args[i + 1])
            ft_putchar(' ');
        i++;
    }
    if (!n_flag)
        ft_putchar('\n');
    return (0);
}

int exec_builtin(char *name, char **args)
{
    printf("argc = %i\n", g_main.cmd_list->argc);
    if (!ft_strcmp(name, "echo"))
        return (ft_echo(args));
    else if (!ft_strcmp(name, "cd"))
        return (ft_cd(args));
    else if (!ft_strcmp(name, "pwd"))
        return (ft_pwd());
    // else if (!ft_strcmp(name, "setenv"))
    //     return (ft_setenv(args));
    // else if (!ft_strcmp(name, "unsetenv"))
    //     return (ft_unsetenv(args));
    // else if (!ft_strcmp(name, "env"))
    //     return (ft_env(args));
    // else if (!ft_strcmp(name, "exit"))
    //     return (ft_exit(args));
    return (0);
}
