/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:04:01 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/03 19:13:17 by codk             ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	uint64_t		last_meal;
	pthread_mutex_t	mutex_meal;
	struct s_data	*data;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	int				nb;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;

	int				nb_meal;
	uint64_t		start_time;
	volatile int	finished;
	pthread_mutex_t	mutex_finish;

	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_data;

//	UTILS

uint64_t			ft_time(void);
void				ft_print_action(t_philo *p, char *s);
void				ft_check(uint64_t duration_ms, t_data *d);
void				mutex_unlock_all(int argv, ...);
int					ft_atoi(const char *s);

//	INIT

int					ft_check_av(int ac, char **av);
void				ft_init_var_data(int ac, char **av, t_data *d);
int					ft_init_var_philo(t_data *d);
int					ft_init_thread(t_data *d);
void				ft_free_data(t_data *d);

//	ROUTINE

void				*routine(void *arg);
void				*routine_for_1(t_data *d, t_philo *p);
int					routine_for_all(t_data *d, t_philo *p);
int					routine_for_all_b(t_data *d, t_philo *p);
int					ft_isspace(char c);

//	MONITOR

void				*monitor(void *arg);
void				monitor_dead(t_data *d, int i);
void				monitor_meal(t_data *d);
void				ft_fork_order_p(t_philo *p, pthread_mutex_t **first,
						pthread_mutex_t **second);
void				ft_fork_order_i(t_philo *p, pthread_mutex_t **first,
						pthread_mutex_t **second);

//	MAIN

int					ft_isdigit(int c);
int64_t				ft_atoi64(char *s);

#endif
