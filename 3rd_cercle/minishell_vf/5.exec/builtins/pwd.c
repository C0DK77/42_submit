/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:04 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 00:22:44 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(t_command *cmd, t_shell *s)
{
	char	buf[4096];

	(void)cmd;
	(void)s;
	if (getcwd(buf, sizeof buf))
		return (ft_putall_fd(STDOUT_FILENO, 2, buf, "\n"), 0);
	return (perror("pwd"), 1);
}
