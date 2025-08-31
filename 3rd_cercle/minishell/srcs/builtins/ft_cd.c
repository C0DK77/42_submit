/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:22:46 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/31 18:39:55 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  args_len(char **av)
{
    int n;

    n = 0;
    if (!av)
        return (0);
    while (av[n])
        n++;
    return (n);
}

int ft_cd(char **s, t_envp *l)
{
    char    *target;
    char    *pwd_before;
    int     argc;

    argc = args_len(s);
    pwd_before = ft_env_search_value(l, "PWD");
    target = ft_cd_conditions(s, l, NULL, argc);
    if (target == NULL)
        return (1);
    if (chdir(target) != 0)
        return (ft_cd_error(1, NULL), 1);
    update_pwd_vars(l, pwd_before);
    g_exit_status = 0;
    return (0);
}

char    *ft_cd_conditions(char **s, t_envp *l, char *target, int i)
{

    if (i > 2)
        return (ft_cd_error(0, NULL));

    if (i == 1)
    {
        if (!ft_cd_search_var(l, "HOME"))
            return (NULL);
        target = ft_env_search_value(l, "HOME");
    }
    else if (i > 1 && s[1])
    {
        if (ft_strcmp(s[1], "-") == 0)
        {
            if (!ft_cd_search_var(l, "OLDPWD"))
                return (NULL);
            target = ft_env_search_value(l, "OLDPWD");
        }
        else if (ft_strcmp(s[1], "--") == 0)
        {
            if (!ft_cd_search_var(l, "HOME"))
                return (NULL);
            target = ft_env_search_value(l, "HOME");
        }
        else if (s[1][0] == '-' && s[1][1] != '\0')
            return (ft_cd_error(2, s[1]));
        else
            target = s[1];
    }
    else
    {
        return (NULL);
    }
    return (target);
}

int ft_cd_search_var(t_envp *l, char *v)
{
    char    *t;

    t = ft_env_search_value(l, v);
    if (!t)
    {
        g_exit_status = 1;
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(v, 2);
        ft_putstr_fd(" not set\n", 2);
        return (0);
    }
    if (ft_strcmp(v, "OLDPWD") == 0)
    {
        ft_putstr_fd(t, 1);
        ft_putstr_fd("\n", 1);
    }
    return (1);
}

char    *ft_cd_error(int i, char *c)
{
    if (i == 0)
    {
        g_exit_status = 1;
        return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), NULL);
    }
    if (i == 1)
    {
        g_exit_status = 1;
        return (perror("minishell: cd"), NULL);
    }
    if (i == 2)
    {
        g_exit_status = 2;
        return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(c, 2),
            ft_putstr_fd(": invalid option\n", 2),
            ft_putstr_fd("cd: usage: cd [dir]\n", 2), NULL);
    }
    return (NULL);
}

