/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/19 21:42:09 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **s, t_envp **l)
{
	if (!s || !s[0]) // Si la commande est vide
		return (0);
	// Comparer la commande avec les built-ins disponibles
	if (ft_strcmp(s[0], "cd") == 0)
	{
		g_exit_status = ft_cd(s, *l);
		return (1);
	}
	else if (ft_strcmp(s[0], "exit") == 0)
	{
		ft_exit(s); // ft_exit gère son propre exit()
		return (1);
	}
	else if (ft_strcmp(s[0], "echo") == 0)
	{
		g_exit_status = ft_echo(s);
		return (1);
	}
	else if (ft_strcmp(s[0], "pwd") == 0)
	{
		g_exit_status = ft_pwd(s, *l);
		return (1);
	}
	else if (ft_strcmp(s[0], "env") == 0)
	{
		g_exit_status = ft_env(*l); // Appel à ft_env
		return (1);
	}
	else if (ft_strcmp(s[0], "export") == 0)
	{
		g_exit_status = ft_export(s, l); // Appel à ft_export
		return (1);
	}
	else if (ft_strcmp(s[0], "unset") == 0)
	{
		g_exit_status = ft_unset(s, l);
		return (1);
	}
	else if (ft_strcmp(s[0], ":") == 0)
	// Le built-in ':' qui ne fait rien et retourne 0
	{
		g_exit_status = 0;
		return (1);
	}
	return (0); // Ce n'est pas un built-in
}
