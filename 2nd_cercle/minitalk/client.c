/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:18:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/03/26 14:36:13 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include "libft.h"

volatile sig_atomic_t	g_ack_received = 0;

void	handle_ack(int sig)
{
	if (sig == SIGUSR1)
	{
		g_ack_received = 1;
		ft_putstr("✅ Message reçu par le serveur !\n");
	}
}

void	ft_send_char(pid_t pid, char c)
{
	int	i;

	for (i = 0; i < 8; i++)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
	}
}

void	ft_send_string(pid_t pid, char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\0');
}

int main (int ac, char **av)
{
	struct sigaction sa;
    pid_t server_pid;

	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	if (ac != 3)
	{
		ft_putstr(" ⛔ Client must take 2 arguments\n");
		ft_putstr(" ================================\n");
		ft_putstr(" EXEXUTABLE     PID    \"STRING\"\n");
		return 1;
	}
	
    server_pid = ft_atoi(av[1]);
    ft_send_string(server_pid, av[2]);
    while (!g_ack_received)
		pause();

	return (0);
}