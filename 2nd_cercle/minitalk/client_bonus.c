/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:17:09 by cdesjars          #+#    #+#             */
/*   Updated: 2025/05/28 03:39:47 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static t_client	g_client;

void	handle_ack(int sig)
{
	(void)sig;
	g_client.ack_received = 1;
}

void	handle_end(int sig)
{
	(void)sig;
	g_client.end_received = 1;
}

void	send_char(pid_t pid, unsigned char c)
{
	int	sig;
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		g_client.ack_received = 0;
		if (kill(pid, sig) == -1)
			return ;
		while (!g_client.ack_received)
			pause();
		bit--;
	}
}

int	main(int argc, char **argv)
{
	char	*str;

	if (argc != 3)
	{
		ft_putstr("Le client doit prendre 2 parametres : [PID] [CHAINE]\n");
		return (1);
	}
	str = argv[2];
	g_client.server_pid = (pid_t)ft_atoi(argv[1]);
	g_client.ack_received = 0;
	g_client.end_received = 0;
	signal(SIGUSR1, handle_ack);
	signal(SIGUSR2, handle_end);
	while (*str)
		send_char(g_client.server_pid, *str++);
	send_char(g_client.server_pid, '\0');
	while (!g_client.end_received)
		pause();
	ft_putstr("Le serveur a bien reçu le message\n");
	return (0);
}
