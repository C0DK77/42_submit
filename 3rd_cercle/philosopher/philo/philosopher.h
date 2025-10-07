/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:04:01 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/07 03:59:41 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define DIED "\033[1;31m"
# define TIME "\033[32m"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nb_meal;
	int					nb;
	uint64_t			start_time;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int					finished;
	pthread_t			monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		mutex_finish;
	t_philo				**philo;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	unsigned int		times;
	uint64_t			last_meal;
	unsigned int		forks[2];
	pthread_mutex_t		mutex_meal;
	t_data				*data;
}						t_philo;

//	INIT

t_data					*ft_init_var_data(int ac, char **av);
t_philo					**ft_init_var_philo(t_data *d);
void					ft_forks(t_philo *p);
pthread_mutex_t			*ft_init_forks(t_data *d);

//	PROGRAM

int						ft_start_philo(t_data *d);
void					ft_stop_philo(t_data *d);
void					ft_free_data(t_data *d);

//	MONITOR

void					ft_monitor_set_stop_flag(t_data *d, int i);
int						ft_monitor_check_stop_flag(t_data *d);
int						kill_philo(t_philo *p);
int						ft_program_condition(t_data *d);
void					*ft_monitor(void *d);

//	ROUTINE

void					*ft_routine(void *arg);
void					*ft_routine_for_1(t_philo *p);
void					ft_routine_think(t_philo *p, int i);
void					ft_routine_sleep(t_data *d, uint64_t i);
void					ft_routine_for_all(t_philo *p);

//	UTILS

int						ft_check_av(int ac, char **av);
int						ft_isspace(char c);
int						ft_atoi(const char *s);
int						ft_isdigit(int c);
int64_t					ft_atoi64(char *s);

uint64_t				ft_time(void);
void					ft_print_action(t_philo *p, char *s, int i);
void					ft_check(uint64_t duration_ms, t_data *d);
void					ft_mutex_unlock_all(int argv, ...);

#endif
