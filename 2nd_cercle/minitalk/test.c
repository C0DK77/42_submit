/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:54:54 by codk              #+#    #+#             */
/*   Updated: 2025/03/25 11:50:43 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void ft_putchar (char c)
{
    write(1, &c, 1);
}

int ft_strlen (char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return i;
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
		ft_putchar("-");
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + 48);
}

void handler (int sig)
{
    static int i;
    if (sig == SIGUSR1)
    {
        write(1, "SIGUSR1 reçu ", 14);
        ft_putnbr(i);
        write(1, " fois\n", 5);
    }
}

int main (void)
{
    int pid;
    pid = getpid();
    signal(SIGUSR1, handler);
    ft_putstr("En attente du signal ... PID :");
    ft_putnbr(pid);
    while(1)
        pause();
}