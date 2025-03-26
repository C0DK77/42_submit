#ifndef MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_send_char(pid_t pid, char c);
void signal_handler (int sig, siginfo_t *info, void *context);
void	ft_send_string(pid_t pid, char *str);

#endif