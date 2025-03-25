/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:52:58 by codk              #+#    #+#             */
/*   Updated: 2025/03/25 23:28:12 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ft_putchar (char c)
{
    write(1, &c, 1);
}

void ft_putstr(char *str)
{
    while (*str)
        ft_putchar(*str++);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + 48);
}

void signal_handler (int sig, siginfo_t *info, void *context)
{
    static int bit;
    static char c;
    bit = 0;
    if (sig == SIGUSR2)
		c |= (1 << bit);
    bit++;
    if (bit == 8)
    {
        ft_putchar(c);
        if (c == '\0')
        {
            ft_putstr("Fin de message");
            ft_putchar('\n');
        }
        c = 0;
        bit = 0;
    }
}

int main (void)
{
    struct sigaction    sa;
    // memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL); // bit = 0
	sigaction(SIGUSR2, &sa, NULL); // bit = 1
    
    ft_putstr("🔔 PID du processus : ");
    ft_putnbr(getpid());
    ft_putstr("\n📬 En attente d'un signal ...\n");
    while (1)
        pause();
}