/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:18:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/03/25 23:25:38 by codk             ###   ########.fr       */
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

// char	ft_convert_char_to_bit(char c)
// {
// 	int		i;
// 	char	*s;

// 	i = 0;
// 	s = (char *)malloc(sizeof(char) * 9);
// 	if (!s)
// 		return (NULL);
// 	while (i < 8)
// 	{
// 		s[i] = (c * 2) + 48;
// 		c /= 2;
// 		i--;
// 	}
// }

void	ft_send_char(pid_t pid, char c)
{
	int	i;

	for (i = 0; i < 8; i++)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
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
    pid_t server_pid;
    server_pid = atoi(av[1]);
    ft_send_string(server_pid, av[2]);
    return 0;
}