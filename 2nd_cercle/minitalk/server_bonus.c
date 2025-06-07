/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:16:34 by cdesjars          #+#    #+#             */
/*   Updated: 2025/05/28 03:09:17 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk_bonus.h"
#include <signal.h>
#include <unistd.h>

static t_server	g_server;

void	handle_bit(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_server.client_pid == 0)
		g_server.client_pid = info->si_pid;
	g_server.char_acc <<= 1;
	if (sig == SIGUSR2)
		g_server.char_acc |= 1;
	++g_server.bit_count;
	if (g_server.bit_count == 8)
	{
		write(1, &g_server.char_acc, 1);
		if (g_server.char_acc == '\0')
		{
			write(1, "\n", 1);
			kill(g_server.client_pid, SIGUSR2);
		}
		g_server.char_acc = 0;
		g_server.bit_count = 0;
	}
	kill(g_server.client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	g_server.client_pid = 0;
	g_server.bit_count = 0;
	g_server.char_acc = 0;
	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	sa.sa_sigaction = handle_bit;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
