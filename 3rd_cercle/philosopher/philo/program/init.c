/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:48:26 by cdesjars          #+#    #+#             */
/*   Updated: 2025/10/04 04:18:34 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_data	*ft_init_var_data(int ac, char **av, int i)
{
	t_data	*d;

	d = malloc(sizeof(t_data) * 1);
	if (!d)
		return (NULL);
	d->nb = ft_atoi(av[1]);
	d->time_to_die = ft_atoi64(av[2]);
	d->time_to_eat = ft_atoi64(av[3]);
	d->time_to_sleep = ft_atoi64(av[4]);
	d->nb_meal = -1;
	if (ac == 6)
		d->nb_meal = ft_atoi(av[5]);
	d->philo = ft_init_var_philo(d);
	if (!d->philo)
		return (NULL);
	d->forks = ft_init_forks(d);
	if (!d->forks)
		return (NULL);
	if (pthread_mutex_init(&d->mutex_finish, 0) != 0)
		return (NULL);
	if (pthread_mutex_init(&d->print, 0) != 0)
		return (NULL);
	d->finished = 0;
	return (d);
}

t_philo	**ft_init_var_philo(t_data *d)
{
	int		i;
	t_philo	**p;

	i = 0;
	p = malloc(sizeof(t_philo) * d->nb);
	if (!p)
		return (0);
	while (i < d->nb)
	{
		p[i] = malloc(sizeof(t_philo) * 1);
		if (!p[i])
			return (0);
		if (pthread_mutex_init(&p[i]->mutex_meal, 0) != 0)
			return (0);
		p[i]->data = d;
		p[i]->id = i + 1;
		p[i]->times = 0;
		ft_forks(p[i]);
		i++;
	}
	return (p);
}

void	ft_forks(t_philo *p)
{
	p->forks[0] = p->id;
	p->forks[1] = (p->id + 1) % p->data->nb;
	if (p->id % 2)
	{
		p->forks[0] = (p->id + 1) % p->data->nb;
		p->forks[1] = p->id;
	}
}

pthread_mutex_t	*ft_init_forks(t_data *d)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * d->nb);
	if (!forks)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < d->nb)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null(STR_ERR_MUTEX, NULL, 0));
		i++;
	}
	return (forks);
}
