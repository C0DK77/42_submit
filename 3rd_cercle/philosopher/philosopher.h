/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:47:19 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/24 10:27:38 by corentindes      ###   ########.fr       */
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

# define LIMIT_MAX_INT64_T 9223372036854775807

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				*dead;
	t_data			*data;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	uint64_t		last_meal;

}					t_philo;

typedef struct s_data
{
	int				nb;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		nb_times_to_eat;
	uint64_t		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}					t_data;

int64_t				ft_atoi(char *s);
int					ft_isdigit(char c);
int					ft_isspace(char c);
void				ft_putchar(char c);
void				ft_putstr(char *s);

int					thread_init(t_data *d);
int					check_args(int argc, char **argv);
void				variables_data_init(int argc, char **argv, t_data *d);
int					variables_philos_init(t_data *d);
void				*monitor(t_data *d, t_philo *p);
void				*routine(void *args);
void				free_data(t_data *d);

#endif
