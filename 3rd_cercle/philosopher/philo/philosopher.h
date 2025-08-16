/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:04:01 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 12:24:53 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	uint64_t		last_meal;
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

	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_data;

//	UTILS

uint64_t			ft_time(void);
void				ft_print_action(t_philo *p, char *s);
void				ft_check_sleep(uint64_t duration_ms, t_data *d);
void				ft_free_data(t_data *d);

//	INIT

int					ft_check_av(int ac, char **av);
void				ft_init_var_data(int ac, char **av, t_data *d);
int					ft_init_var_philo(t_data *d);
int					ft_init_thread(t_data *d);

//	ROUTINE

void				*routine(void *arg);
void				*routine_for_1(t_data *d, t_philo *p);
int					routine_for_all(t_data *d, t_philo *p);

//	MONITOR

void				*monitor(void *arg);
void				monitor_dead(t_data *d, int i);
void				monitor_meal(t_data *d);

#endif
