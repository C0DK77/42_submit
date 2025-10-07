/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:32:46 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 04:32:48 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		g_signal_received = 0;

void	signal_handler(int sig)
{
	g_signal_received = sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	check_signals(void)
{
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		return (1);
	}
	return (0);
}

void	reset_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
