/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:28:42 by codk              #+#    #+#             */
/*   Updated: 2025/05/23 22:50:16 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

void	ft_send_char(pid_t pid, char c);
void	ft_signal_handler(int sig, siginfo_t *info, void *context);
void	ft_send_string(pid_t pid, char *str);
void	ft_handle_ack(int sig);

#endif
