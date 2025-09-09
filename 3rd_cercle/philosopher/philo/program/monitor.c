/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:12:15 by cdesjars          #+#    #+#             */
/*   Updated: 2025/09/09 09:10:39 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

void	*monitor(void *arg)
{
	int		i;
	t_data	*d;

	i = 0;
	d = (t_data *)arg;
	while (!d->finished)
	{
		while (i < d->nb)
		{
			monitor_dead(d, i);
			i++;
		}
		i = 0;
		if (d->nb_meal != -1)
			monitor_meal(d);
		usleep(100);
	}
	return (NULL);
}

void	monitor_dead(t_data *d, int i)
{
	uint64_t	last_meal_time;

	pthread_mutex_lock(&d->philo[i].mutex_meal);
	last_meal_time = d->philo[i].last_meal;
	pthread_mutex_unlock(&d->philo[i].mutex_meal);
	if (ft_time() - last_meal_time > d->time_to_die)
	{
		pthread_mutex_lock(&d->mutex_finish);
		if (!d->finished)
		{
			d->finished = 1;
			pthread_mutex_unlock(&d->mutex_finish);
			pthread_mutex_lock(&d->print);
			printf(TIME "%lu \033[0m", ft_time() - d->start_time);
			printf(DIED "%d died\033[0m\n", d->philo[i].id);
			pthread_mutex_unlock(&d->print);
		}
		else
			pthread_mutex_unlock(&d->mutex_finish);
	}
}

void	monitor_meal(t_data *d)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < d->nb)
	{
		pthread_mutex_lock(&d->philo[i].mutex_meal);
		if (d->philo[i].meals_eaten >= d->nb_meal)
			full++;
		pthread_mutex_unlock(&d->philo[i].mutex_meal);
		i++;
	}
	if (full == d->nb)
	{
		pthread_mutex_lock(&d->mutex_finish);
		d->finished = 1;
		pthread_mutex_unlock(&d->mutex_finish);
	}
}
