/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:16:40 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/23 05:54:34 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
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
		ft_routine_think(p, 1);
	while (ft_monitor_check_stop_flag(p->data) == 0)
	{
		ft_routine_for_all(p);
		ft_routine_think(p, 0);
	}
	return (NULL);
}

void	*ft_routine_for_1(t_philo *p)
{
	pthread_mutex_lock(&p->data->forks[p->forks[0]]);
	ft_print_action(p, "has taken a fork", 0);
	ft_routine_sleep(p->data, p->data->time_to_die);
	ft_print_action(p, "died", 0);
	pthread_mutex_unlock(&p->data->forks[p->forks[0]]);
	return (NULL);
}

void	ft_routine_think(t_philo *p, int i)
{
	time_t	time_to_think;

	pthread_mutex_lock(&p->mutex_meal);
	time_to_think = (p->data->time_to_die - (ft_time() - p->last_meal)
			- p->data->time_to_eat) / 2;
	pthread_mutex_unlock(&p->mutex_meal);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && i == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (i == 0)
		ft_print_action(p, "is thinking", 0);
	ft_routine_sleep(p->data, time_to_think);
}

void	ft_routine_sleep(t_data *d, uint64_t i)
{
	uint64_t	t;

	t = ft_time() + i;
	while (ft_time() < t)
	{
		if (ft_monitor_check_stop_flag(d))
			break ;
		usleep(100);
	}
}

void	ft_routine_for_all(t_philo *p)
{
	pthread_mutex_lock(&p->data->forks[p->forks[0]]);
	ft_print_action(p, "has taken a fork", 0);
	pthread_mutex_lock(&p->data->forks[p->forks[1]]);
	ft_print_action(p, "has taken a fork", 0);
	ft_print_action(p, "is eating", 0);
	pthread_mutex_lock(&p->mutex_meal);
	p->last_meal = ft_time();
	pthread_mutex_unlock(&p->mutex_meal);
	ft_routine_sleep(p->data, p->data->time_to_eat);
	if (ft_monitor_check_stop_flag(p->data) == 0)
	{
		pthread_mutex_lock(&p->mutex_meal);
		p->times += 1;
		pthread_mutex_unlock(&p->mutex_meal);
	}
	ft_print_action(p, "is sleeping", 0);
	pthread_mutex_unlock(&p->data->forks[p->forks[1]]);
	pthread_mutex_unlock(&p->data->forks[p->forks[0]]);
	ft_routine_sleep(p->data, p->data->time_to_sleep);
}
