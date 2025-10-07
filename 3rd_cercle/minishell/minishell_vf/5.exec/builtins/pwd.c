/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:41:04 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 04:41:06 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(t_command *cmd, t_shell *sh)
{
	char	buf[4096];

	(void)cmd;
	(void)sh;
	if (getcwd(buf, sizeof buf))
	{
		write(STDOUT_FILENO, buf, ft_strlen(buf));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	perror("pwd");
	return (1);
}
