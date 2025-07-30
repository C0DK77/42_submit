#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define LIMIT_MAX_INT64_T 9223372036854775807

struct s_data;

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
	int				nb_times_to_eat;
	uint64_t		start_time;
	int				finished;

	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}					t_data;

int64_t				ft_atoi_int64(char *s);
uint64_t			get_time(void);
void				print_action(t_philo *p, char *msg);

int					check_args(int argc, char **argv);
void				variables_data_init(int argc, char **argv, t_data *d);
int					variables_philos_init(t_data *d);
int					thread_init(t_data *d);
void				*routine(void *args);
void				*monitor(void *arg);
void				free_data(t_data *d);

#endif
