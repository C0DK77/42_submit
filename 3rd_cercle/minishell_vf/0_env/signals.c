/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:32:46 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 00:55:04 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_signal_received = 0;

void	ft_signal_init(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_handler(int i)
{
	g_signal_received = i;
	if (i == SIGINT)
	{
		ft_putchar("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_signal_check(void)
{
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		return (1);
	}
	return (0);
}

void	ft_signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
