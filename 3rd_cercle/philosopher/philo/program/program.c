/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:12:15 by cdesjars          #+#    #+#             */
/*   Updated: 2025/10/04 04:21:13 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_start_philo(t_data *d)
{
	int	i;

	i = 0;
	d->start_time = ft_time() + (d->nb * 2 * 10);
	while (i < d->nb)
	{
		if (pthread_create(&d->philo[i].thread, NULL, &routine,
				&d->philo[i]) != 0)
			return (0);
		i++;
	}
	if (d->nb > 1 && pthread_create(&d->grim_reaper, NULL, &grim_reaper,
			d) != 0)
		return (0);
	return (1);
}

void	ft_stop_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		pthread_join(d->philo[i].thread, NULL);
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
		pthread_mutex_destroy(&d->philo[i].mutex_meal);
		i++;
	}
	pthread_mutex_destroy(&d->print);
	pthread_mutex_destroy(&d->mutex_finish);
	free(d->philo);
	free(d->forks);
	free(d);
}
