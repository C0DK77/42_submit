/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:16:40 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/09 09:55:57 by codk             ###   ########.fr       */
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
	while (1)
	{
		pthread_mutex_lock(&d->mutex_finish);
		if (d->finished)
		{
			pthread_mutex_unlock(&d->mutex_finish);
			break ;
		}
		pthread_mutex_unlock(&d->mutex_finish);
		if (!routine_for_all(d, p))
			break ;
	}
	return (NULL);
}

void	*routine_for_1(t_data *d, t_philo *p)
{
	ft_print_action(p, "has taken one fork");
	ft_check(d->time_to_die, d);
	pthread_mutex_lock(&d->print);
	pthread_mutex_lock(&d->mutex_finish);
	if (!d->finished)
	{
		printf(TIME "%lu \033[0m", ft_time() - d->start_time);
		printf(DIED "%d died\033[0m\n", p->id);
		d->finished = 1;
	}
	pthread_mutex_unlock(&d->mutex_finish);
	pthread_mutex_unlock(&d->print);
	return (NULL);
}

void	ft_fork_order(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s)
{
	if (p->l_fork < p->r_fork)
	{
		*f = p->l_fork;
		*s = p->r_fork;
	}
	else
	{
		*f = p->r_fork;
		*s = p->l_fork;
	}
}

int	routine_for_all(t_data *d, t_philo *p)
{
	pthread_mutex_t	*f;
	pthread_mutex_t	*s;

	ft_fork_order(p, &f, &s);
	pthread_mutex_lock(f);
	pthread_mutex_lock(&d->mutex_finish);
	if (d->finished)
		return (mutex_unlock_all(2, &d->mutex_finish, f), 0);
	pthread_mutex_unlock(&d->mutex_finish);
	ft_print_action(p, "has taken a fork");
	pthread_mutex_lock(s);
	pthread_mutex_lock(&d->mutex_finish);
	if (d->finished)
		return (mutex_unlock_all(3, &d->mutex_finish, s, f), 0);
	pthread_mutex_unlock(&d->mutex_finish);
	ft_print_action(p, "has taken a fork");
	ft_print_action(p, "is eating");
	ft_check(d->time_to_eat, d);
	pthread_mutex_lock(&p->mutex_meal);
	p->last_meal = ft_time();
	p->meals_eaten++;
	mutex_unlock_all(3, &p->mutex_meal, s, f);
	return (routine_for_all_b(d, p));
}

int	routine_for_all_b(t_data *d, t_philo *p)
{
	int	is_finished;

	pthread_mutex_lock(&d->mutex_finish);
	is_finished = d->finished;
	pthread_mutex_unlock(&d->mutex_finish);
	if (is_finished)
		return (0);
	ft_print_action(p, "is thinking");
	pthread_mutex_lock(&d->mutex_finish);
	is_finished = d->finished;
	pthread_mutex_unlock(&d->mutex_finish);
	if (is_finished)
		return (0);
	ft_print_action(p, "is sleeping");
	ft_check(d->time_to_sleep, d);
	return (1);
}
