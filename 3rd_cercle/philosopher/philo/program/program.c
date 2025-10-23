/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:12:15 by cdesjars          #+#    #+#             */
/*   Updated: 2025/10/23 05:49:54 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_start_philo(t_data *d)
{
	int	i;

	i = 0;
	d->start_time = ft_time() + (d->nb * 2 * 10);
	while (i < d->nb)
	{
		if (pthread_create(&d->philo[i]->thread, NULL, &ft_routine,
				d->philo[i]) != 0)
			return (0);
		i++;
	}
	if (d->nb > 1 && pthread_create(&d->monitor, NULL, &ft_monitor, d) != 0)
		return (0);
	return (1);
}

void	ft_stop_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		pthread_join(d->philo[i]->thread, NULL);
		i++;
	}
	ft_free_data(d);
}

void	ft_free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		pthread_mutex_destroy(&d->forks[i]);
		pthread_mutex_destroy(&d->philo[i]->mutex_meal);
		i++;
	}
	pthread_mutex_destroy(&d->print);
	pthread_mutex_destroy(&d->mutex_finish);
	free(d->philo);
	free(d->forks);
	free(d);
}
