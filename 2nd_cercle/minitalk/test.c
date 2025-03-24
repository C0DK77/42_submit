/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:54:54 by codk              #+#    #+#             */
/*   Updated: 2025/03/24 22:10:10 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void ft_putstr(char str)
{
    int i;
    i = 0;
    while (str[i])
    {
        write(1, (char)str[i], 1);
        i++;
    }
}

void handler (int sig)
{
    if (sig == SIGUSR1)
        write(1, "SIGUSR1 reçu", 12);
}

int main (void)
{
    int pid;
    pid = getpid;
    signal(SIGUSR1, handler);
    ft_putstr("En attente du signal ... PID :");
    while(1)
        pause();
}