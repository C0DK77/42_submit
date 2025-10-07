/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 02:34:47 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 03:34:52 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_monitor(void *d)
{
	t_data	*t;

	t = (t_data *)d;
	if (t->nb_meal == 0)
		return (NULL);
	ft_monitor_set_stop_flag(t, 0);
	while (ft_time() < t->start_time)
		continue ;
	while (1)
	{
		if (ft_program_condition(t) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	ft_monitor_set_stop_flag(t_data *d, int i)
{
	pthread_mutex_lock(&d->mutex_finish);
	d->finished = i;
	pthread_mutex_unlock(&d->mutex_finish);
}

int	ft_monitor_check_stop_flag(t_data *d)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&d->mutex_finish);
	if (d->finished == 1)
		i = 1;
	pthread_mutex_unlock(&d->mutex_finish);
	return (i);
}

int	kill_philo(t_philo *p)
{
	time_t	time;

	time = ft_time();
	if ((time - p->last_meal) >= p->data->time_to_die)
	{
		ft_monitor_set_stop_flag(p->data, 1);
		ft_print_action(p, "died", 1);
		pthread_mutex_unlock(&p->mutex_meal);
		return (1);
	}
	return (0);
}

int	ft_program_condition(t_data *d)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (i < d->nb)
	{
		pthread_mutex_lock(&d->philo[i]->mutex_meal);
		if (kill_philo(d->philo[i]))
			return (1);
		if (d->nb_meal != -1)
			if (d->philo[i]->times < (unsigned int)d->nb_meal)
				j = 0;
		pthread_mutex_unlock(&d->philo[i]->mutex_meal);
		i++;
	}
	if (d->nb_meal != -1 && j == 1)
		return (ft_monitor_set_stop_flag(d, 1), 1);
	return (0);
}
