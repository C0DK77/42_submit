/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:48:26 by cdesjars          #+#    #+#             */
/*   Updated: 2025/09/02 20:23:15 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

int	ft_check_av(int ac, char **av)
{
	int	i;

	i = 1;
	if (!(ac == 5 || ac == 6))
		return (0);
	if (ft_atoi64(av[1]) < 1 || ft_atoi64(av[1]) > 200)
	{
		ft_putstr("Number of philosophers must be\n");
		ft_putstr("  1 <= Philosophers <= 200\n");
		return (0);
	}
	while (i < ac)
	{
		if (ft_atoi64(av[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_init_var_data(int ac, char **av, t_data *d)
{
	d->nb = ft_atoi(av[1]);
	d->time_to_die = ft_atoi64(av[2]);
	d->time_to_eat = ft_atoi64(av[3]);
	d->time_to_sleep = ft_atoi64(av[4]);
	if (ac == 6)
		d->nb_meal = ft_atoi(av[5]);
	else
		d->nb_meal = -1;
	d->finished = 0;
	d->start_time = ft_time();
	pthread_mutex_init(&d->print, NULL);
	pthread_mutex_init(&d->mutex_finish, NULL);
}

int	ft_init_var_philo(t_data *d)
{
	int	i;

	i = 0;
	d->philo = malloc(sizeof(t_philo) * d->nb);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->nb);
	if (!d->philo || !d->forks)
		return (0);
	while (i < d->nb)
	{
		pthread_mutex_init(&d->forks[i], NULL);
		pthread_mutex_init(&d->philo[i].mutex_meal, NULL);
		d->philo[i].id = i + 1;
		d->philo[i].meals_eaten = 0;
		d->philo[i].data = d;
		d->philo[i].l_fork = &d->forks[i];
		d->philo[i].r_fork = &d->forks[(i + 1) % d->nb];
		d->philo[i].last_meal = ft_time();
		i++;
	}
	return (1);
}

int	ft_init_thread(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		if (pthread_create(&d->philo[i].thread, NULL, routine,
				&d->philo[i]) != 0)
			return (0);
		usleep(100);
		i++;
	}
	return (1);
}

void	ft_free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		pthread_mutex_destroy(&d->forks[i]);
		pthread_mutex_destroy(&d->philo[i].mutex_meal);
		i++;
	}
	pthread_mutex_destroy(&d->print);
	pthread_mutex_destroy(&d->mutex_finish);
	free(d->philo);
	free(d->forks);
	free(d);
}
