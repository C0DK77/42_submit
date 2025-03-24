/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:54:54 by codk              #+#    #+#             */
/*   Updated: 2025/03/24 23:16:09 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

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
    int i;
    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

void	ft_putnbr(int n)
{
	int	a;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	a = (n % 10) + 48;
	write(1, &a, 1);
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