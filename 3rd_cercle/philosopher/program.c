/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:16:40 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/13 16:17:32 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

int	ft_check_av(int ac, char **av)
{
	int	i;

	i = 0;
	if (!(ac == 5 || ac == 6))
		return (0);
	if (ft_atoi64(av[1]) < 1 || ft_atoi64(av[1]) > 200)
	{
		ft_putstr("Number of philosophers must be between 1 and 200 included.\n");
		return (0);
	}
	while (i < ac)
	{
		if (ft_atoi64(av[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_init_var_data(int ac, char **av, t_data *d)
{
	d->nb = ft_atoi64(av[1]);
	d->time_to_die = ft_atoi64(av[2]);
	d->time_to_eat = ft_atoi64(av[3]);
	d->time_to_sleep = ft_atoi64(av[4]);
	d->nb_times_to_eat = (ac == 6) ? ft_atoi64(av[5]) : -1;
	d->finished = 0;
	d->start_time = ft_time();
	pthread_mutex_init(&d->print_mutex, NULL);
}

int	ft_init_var_philo(t_data *d)
{
	int	i;

	i = 0;
	d->philos = malloc(sizeof(t_philo) * d->nb);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->nb);
	if (!d->philos || !d->forks)
		return (0);
	while (i < d->nb)
	{
		pthread_mutex_init(&d->forks[i], NULL);
		d->philos[i].id = i + 1;
		d->philos[i].meals_eaten = 0;
		d->philos[i].data = d;
		d->philos[i].l_fork = &d->forks[i];
		d->philos[i].r_fork = &d->forks[(i + 1) % d->nb];
		d->philos[i].last_meal = ft_time();
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*d;
	int		full;

	i = 0;
	d = (t_data *)arg;
	while (!d->finished)
	{
		while (i < d->nb)
		{
			if (ft_time() - d->philos[i].last_meal > d->time_to_die)
			{
				pthread_mutex_lock(&d->print_mutex);
				printf("%llu %d died\n", ft_time() - d->start_time,
					d->philos[i].id);
				d->finished = 1;
				pthread_mutex_unlock(&d->print_mutex);
				return (NULL);
			}
			i++;
		}
		i = 0;
		if (d->nb_times_to_eat != -1)
		{
			full = 0;
			while (i < d->nb)
			{
				if (d->philos[i].meals_eaten >= d->nb_times_to_eat)
					full++;
				i++;
			}
			if (full == d->nb)
				d->finished = 1;
		}
		usleep(100);
	}
	return (NULL);
}

int	ft_init_thread(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		if (pthread_create(&d->philos[i].thread, NULL, routine,
				&d->philos[i]) != 0)
			return (0);
		usleep(100);
		i++;
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)arg;
	d = p->data;
	if (d->nb == 1)
	{
		ft_print_action(p, "has taken a fork");
		ft_check_sleep(d->time_to_die, d);
		pthread_mutex_lock(&d->print_mutex);
		if (!d->finished)
		{
			printf("%llu %d died\n", ft_time() - d->start_time, p->id);
			d->finished = 1;
		}
		pthread_mutex_unlock(&d->print_mutex);
		return (NULL);
	}
	while (!d->finished)
	{
		ft_print_action(p, "is thinking");
		if (d->finished)
			break ;
		pthread_mutex_lock(p->l_fork);
		ft_print_action(p, "has taken a fork");
		if (d->finished)
		{
			pthread_mutex_unlock(p->l_fork);
			break ;
		}
		pthread_mutex_lock(p->r_fork);
		ft_print_action(p, "has taken a fork");
		pthread_mutex_lock(&d->print_mutex);
		p->last_meal = ft_time();
		pthread_mutex_unlock(&d->print_mutex);
		ft_print_action(p, "is eating");
		ft_check_sleep(d->time_to_eat, d);
		p->meals_eaten++;
		pthread_mutex_unlock(p->r_fork);
		pthread_mutex_unlock(p->l_fork);
		if (d->finished)
			break ;
		ft_print_action(p, "is sleeping");
		ft_check_sleep(d->time_to_sleep, d);
	}
	return (NULL);
}

void	ft_free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb)
	{
		pthread_mutex_destroy(&d->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&d->print_mutex);
	free(d->philos);
	free(d->forks);
	free(d);
}
