/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:16:40 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/04 04:46:44 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->data->nb_meal == 0)
		return (NULL);
	pthread_mutex_lock(&p->mutex_meal);
	p->last_meal = p->data->start_time;
	pthread_mutex_unlock(&p->mutex_meal);
	while (ft_time() < p->data->start_time)
		continue ;
	if (p->data->time_to_die == 0)
		return (NULL);
	if (p->data->nb == 1)
		return (ft_routine_for_1(p));
	else if (p->id % 2)
		ft_routine_think(p, true);
	while (ft_monitor_dead(p->data) == false)
	{
		ft_routine_for_all(p);
		ft_routine_think(p, false);
		return (NULL);
	}
}

void	*ft_routine_for_1(t_philo *p)
{
	pthread_mutex_lock(&p->data->forks[p->forks[0]]);
	write_status(p, false, GOT_FORK_1);
	philo_sleep(p->data, p->data->time_to_die);
	write_status(p, false, DIED);
	pthread_mutex_unlock(&p->data->forks[p->forks[0]]);
	return (NULL);
}

void	ft_routine_think(t_philo *p, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&p->mutex_meal);
	time_to_think = (p->data->time_to_die - (ft_time() - p->last_meal)
			- p->data->time_to_eat) / 2;
	pthread_mutex_unlock(&p->mutex_meal);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		write_status(p, false, THINKING);
	ft_routine_sleep(p->data, time_to_think);
}

void	ft_routine_sleep(t_data *d, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (has_simulation_stopped(d))
			break ;
		usleep(100);
	}
}

void	ft_routine_for_all(t_philo *p)
{
	pthread_mutex_lock(&p->data->forks[p->forks[0]]);
	write_status(p, false, GOT_FORK_1);
	pthread_mutex_lock(&p->data->forks[p->forks[1]]);
	write_status(p, false, GOT_FORK_2);
	write_status(p, false, EATING);
	pthread_mutex_lock(&p->mutex_meal);
	p->last_meal = ft_time();
	pthread_mutex_unlock(&p->mutex_meal);
	p_sleep(p->data, p->data->time_to_eat);
	if (has_simulation_stopped(p->data) == false)
	{
		pthread_mutex_lock(&p->mutex_meal);
		p->times_ate += 1;
		pthread_mutex_unlock(&p->mutex_meal);
	}
	write_status(p, false, SLEEPING);
	pthread_mutex_unlock(&p->data->forks[p->forks[1]]);
	pthread_mutex_unlock(&p->data->forks[p->forks[0]]);
	p_sleep(p->data, p->data->time_to_sleep);
}
