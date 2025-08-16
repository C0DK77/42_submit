/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:16:40 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 12:43:33 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)arg;
	d = p->data;
	if (d->nb == 1)
		return (routine_for_1(d, p));
	while (!d->finished)
		if (!routine_for_all(d, p))
			break ;
	return (NULL);
}

void	*routine_for_1(t_data *d, t_philo *p)
{
	ft_print_action(p, "has taken one fork");
	ft_check_sleep(d->time_to_die, d);
	pthread_mutex_lock(&d->print);
	if (!d->finished)
	{
		printf("%llu %d died\n", ft_time() - d->start_time, p->id);
		d->finished = 1;
	}
	pthread_mutex_unlock(&d->print);
	return (NULL);
}

int	routine_for_all(t_data *d, t_philo *p)
{
	ft_print_action(p, "is thinking");
	if (d->finished)
		return (0);
	pthread_mutex_lock(p->l_fork);
	ft_print_action(p, "has taken one fork");
	if (d->finished)
	{
		pthread_mutex_unlock(p->l_fork);
		return (0);
	}
	pthread_mutex_lock(p->r_fork);
	ft_print_action(p, "has taken a second fork");
	pthread_mutex_lock(&d->print);
	p->last_meal = ft_time();
	pthread_mutex_unlock(&d->print);
	ft_print_action(p, "is eating");
	ft_check_sleep(d->time_to_eat, d);
	p->meals_eaten++;
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
	if (d->finished)
		return (0);
	ft_print_action(p, "is sleeping");
	ft_check_sleep(d->time_to_sleep, d);
	return (1);
}
