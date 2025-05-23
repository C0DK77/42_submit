/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:18:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/23 22:54:10 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "libft.h"

volatile sig_atomic_t	g_ack_received = 0;

void	ft_send_char(pid_t pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
		i++;
	}
}

void	ft_send_string(pid_t pid, char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\0');
}

void	ft_handle_ack(int sig)
{
	if (sig == SIGUSR1)
	{
		g_ack_received = 1;
		ft_putstr("Message reçu par le serveur\n");
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (ac != 3)
	{
		ft_putstr("Le client doit saisir 2 arguments\n");
		return (1);
	}
	ft_send_string(ft_atoi(av[1]), av[2]);
	while (!g_ack_received)
		pause();
	return (0);
}
