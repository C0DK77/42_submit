/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:18:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/22 16:44:44 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_args(int argc, char **argv)
{
	uint64_t	i;

	if (!(argc <= 7 && argc >= 2))
		return (0);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		ft_putstr("Number of philosopher must be between 1 and 200 included.");
		return (0);
	}
	i = 2;
	while (i <= 5)
	{
		if (i < 0 || i > LIMIT_MAX_INT64_T)
			return (0);
		i++;
	}
	return (1);
}

void	variables_data_init(int argc, char **argv, t_data *d)
{
	int	i;

	i = 1;
	d->nb = ft_atoi(argv[1]);
	d->start_time = 0;
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		d->nb_times_to_eat = ft_atoi(argv[5]);
	else
		d->nb_times_to_eat = -1;
}

int	variables_philos_init(t_data *d)
{
	int	i;

	d->philos = malloc(sizeof(t_philo) * d->nb);
	if (!d->philos)
		return (0);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->nb);
	if (!d->forks)
		return (0);
	d->philos[0].id = 1;
	d->philos[0].meals_eaten = 0;
	d->philos[0].l_fork = &d->forks[0];
	d->philos[0].r_fork = &d->forks[d->nb - 1];
	i = 1;
	while (i < d->nb)
	{
		if (pthread_mutex_init(&d->print_mutex, NULL) != 0)
			return (0);
		d->philos[i].id = i + 1;
		d->philos[i].meals_eaten = 0;
		d->philos[i].l_fork = &d->forks[i];
		d->philos[i].r_fork = &d->forks[i - 1];
		i++;
	}
	return (1);
}

void	*monitor(t_data *d, t_philo *p)
{
	int			i;
	uint64_t	now;
	int			full;

	while (!d->finished)
	{
		i = 0;
		while (i < d->nb && !d->finished)
		{
			now = get_time();
			if (now - d->philos[i].last_meal > d->time_to_die)
			{
				pthread_mutex_lock(&d->print_mutex);
				printf("%llu %d died\n", now - d->start_time, d->philos[i].id);
				d->finished = 1;
				pthread_mutex_unlock(&d->print_mutex);
			}
			i++;
		}
		if (d->meals_nb > 0 && !d->finished)
		{
			full = 0;
			for (int j = 0; j < d->nb; j++)
				if (d->philos[j].meals_eaten >= d->meals_nb)
					full++;
			if (full == d->nb)
				d->finished = 1;
		}
		usleep(1000);
	}
	return (NULL);
}

int	thread_init(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		if (pthread_create(&d->philos[i].thread, NULL, *routine,
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
	while (1)
	{
		print_action(p, "is thinking");
		pthread_mutex_lock(p->l_fork);
		print_action(p, "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		print_action(p, "has taken a fork");
		p->last_meal = gettimeofday();
		print_action(p, "is eating");
		usleep(d->time_to_eat);
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		print_action(p, "is sleeping");
		usleep(d->time_to_sleep * 1000);
	}
	return (1);
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
	free(d->philos);
	free(d->forks);
}

int	main(int argc, char **argv)
{
	t_data *d;
	d = malloc(sizeof(t_data));
	if (!d)
		return (0);
	if (!check_args(argc, argv))
		return (0);
	if (!variables_philos_init(d))
		return (1);
	if (!thread_init(d))
		return (1);
	monitor(d, d->philos);
	free_data(d);
	return (0);
}