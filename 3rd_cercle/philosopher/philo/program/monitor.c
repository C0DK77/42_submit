/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:12:15 by cdesjars          #+#    #+#             */
/*   Updated: 2025/08/16 12:33:10 by corentindes      ###   ########.fr       */
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
	if (ft_time() - d->philo[i].last_meal > d->time_to_die)
	{
		pthread_mutex_lock(&d->print);
		if (!d->finished)
		{
			printf("%llu %d died\n", ft_time() - d->start_time, d->philo[i].id);
			d->finished = 1;
		}
		pthread_mutex_unlock(&d->print);
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
		if (d->philo[i].meals_eaten >= d->nb_meal)
			full++;
		i++;
	}
	if (full == d->nb)
		d->finished = 1;
}
