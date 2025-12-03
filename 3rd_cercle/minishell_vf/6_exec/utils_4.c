/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:26:11 by codk              #+#    #+#             */
/*   Updated: 2025/12/03 12:20:35 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signal_config_last_exit(t_shell *sh, pid_t *p, int i)
{
	int	status;

	status = ft_signal_wait(p, i);
	if (WIFSIGNALED(status))
		sh->last_exit = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		sh->last_exit = WEXITSTATUS(status);
	else
		sh->last_exit = 1;
	if (ft_signal_check())
		sh->last_exit = 130;
}
