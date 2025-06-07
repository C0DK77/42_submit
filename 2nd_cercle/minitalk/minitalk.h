/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:07:41 by cdesjars          #+#    #+#             */
/*   Updated: 2025/05/28 03:02:18 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_client
{
	pid_t					server_pid;
	volatile sig_atomic_t	ack_received;
	volatile sig_atomic_t	end_received;
}							t_client;

typedef struct s_server
{
	pid_t					client_pid;
	int						bit_count;
	unsigned char			char_acc;
}							t_server;

void						handle_bit(int sig, siginfo_t *info, void *context);
void						handle_ack(int sig);
void						handle_end(int sig);
void						send_char(pid_t pid, unsigned char c);

#endif
