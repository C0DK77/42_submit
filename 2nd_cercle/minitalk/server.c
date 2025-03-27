/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:52:58 by codk              #+#    #+#             */
/*   Updated: 2025/03/27 14:35:28 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "libft.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;

	(void)context;
	if (sig == SIGUSR2)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_putchar(c);
		if (c == '\0')
		{
			kill(info->si_pid, SIGUSR1);
			ft_putstr("\n✅ Reception complete !\n");
		}
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr("🔔 PID du processus : ");
	ft_putnbr(getpid());
	ft_putstr("\n📬 En attente d'un signal ...\n");
	while (1)
		pause();
	return (0);
}
