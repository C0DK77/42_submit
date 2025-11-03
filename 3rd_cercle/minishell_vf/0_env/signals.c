/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:32:46 by codk              #+#    #+#             */
/*   Updated: 2025/10/27 18:26:30 by corentindes      ###   ########.fr       */
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
		ft_putchar('\n');
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

int	ft_signal_wait(pid_t *p, int n)
{
	int	i;
	int	st;
	int	last;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	last = 0;
	while (i < n)
	{
		if (waitpid(p[i], &st, 0) > 0)
			last = st;
		i++;
	}
	return (last);
}

void	ft_signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
