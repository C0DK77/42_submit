/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:16:40 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/30 16:17:27 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (!(argc == 5 || argc == 6))
		return (0);
	if (ft_atoi_int64(argv[1]) < 1 || ft_atoi_int64(argv[1]) > 200)
	{
		ft_putstr("Number of philosophers must be between 1 and 200 included.\n");
		return (0);
	}
	while (i < argc)
	{
		if (ft_atoi_int64(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	variables_data_init(int argc, char **argv, t_data *d)
{
	d->nb = ft_atoi_int64(argv[1]);
	d->time_to_die = ft_atoi_int64(argv[2]);
	d->time_to_eat = ft_atoi_int64(argv[3]);
	d->time_to_sleep = ft_atoi_int64(argv[4]);
	d->nb_times_to_eat = (argc == 6) ? ft_atoi_int64(argv[5]) : -1;
	d->finished = 0;
	d->start_time = get_time();
	pthread_mutex_init(&d->print_mutex, NULL);
}

int	variables_philos_init(t_data *d)
{
	int	i;

	i = 0;
	d->philos = malloc(sizeof(t_philo) * d->nb);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->nb);
	if (!d->philos || !d->forks)
		return (0);
	while (i < d->nb)
	{
		pthread_mutex_init(&d->forks[i], NULL);
		d->philos[i].id = i + 1;
		d->philos[i].meals_eaten = 0;
		d->philos[i].data = d;
		d->philos[i].l_fork = &d->forks[i];
		d->philos[i].r_fork = &d->forks[(i + 1) % d->nb];
		d->philos[i].last_meal = get_time();
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*d;
	int		full;

	i = 0;
	d = (t_data *)arg;
	while (!d->finished)
	{
		while (i < d->nb)
		{
			if (get_time() - d->philos[i].last_meal > d->time_to_die)
			{
				pthread_mutex_lock(&d->print_mutex);
				printf("%llu %d died\n", get_time() - d->start_time,
					d->philos[i].id);
				d->finished = 1;
				pthread_mutex_unlock(&d->print_mutex);
				return (NULL);
			}
			i++;
		}
        i = 0;
		if (d->nb_times_to_eat != -1)
		{
			full = 0;
			while (i < d->nb)
			{
				if (d->philos[i].meals_eaten >= d->nb_times_to_eat)
					full++;
				i++;
			}
			if (full == d->nb)
				d->finished = 1;
		}
		usleep(100);
	}
	return (NULL);
}

int	thread_init(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		if (pthread_create(&d->philos[i].thread, NULL, routine,
				&d->philos[i]) != 0)
			return (0);
		usleep(100);
		i++;
	}
	return (1);
}

void	*routine(void *args)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)args;
	d = p->data;
	while (!d->finished)
	{
		print_action(p, "is thinking");
		pthread_mutex_lock(p->l_fork);
		print_action(p, "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		print_action(p, "has taken a fork");
		pthread_mutex_lock(&d->print_mutex);
		p->last_meal = get_time();
		pthread_mutex_unlock(&d->print_mutex);
		print_action(p, "is eating");
		usleep(d->time_to_eat * 1000);
		p->meals_eaten++;
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		print_action(p, "is sleeping");
		usleep(d->time_to_sleep * 1000);
	}
	return (NULL);
}

void	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		pthread_mutex_destroy(&d->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&d->print_mutex);
	free(d->philos);
	free(d->forks);
	free(d);
}
