/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:24:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/04 04:10:13 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

uint64_t	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_action(t_philo *p, char *s)
{
	uint64_t	timestamp;
	t_data		*d;
	int			is_finished;

	d = p->data;
	pthread_mutex_lock(&d->mutex_finish);
	is_finished = d->finished;
	pthread_mutex_unlock(&d->mutex_finish);
	if (is_finished)
		return ;
	pthread_mutex_lock(&d->print);
	timestamp = ft_time() - d->start_time;
	printf(TIME "%lu \033[0m %d %s\n", timestamp, p->id, s);
	pthread_mutex_unlock(&d->print);
}

void	ft_check(uint64_t duration_ms, t_data *d)
{
	uint64_t	start;

	start = ft_time();
	while (1)
	{
		pthread_mutex_lock(&d->mutex_finish);
		if (d->finished)
		{
			pthread_mutex_unlock(&d->mutex_finish);
			break ;
		}
		pthread_mutex_unlock(&d->mutex_finish);
		if (ft_time() - start >= duration_ms)
			break ;
		usleep(100);
	}
}

void	mutex_unlock_all(int argv, ...)
{
	va_list			args;
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	va_start(args, argv);
	while (i < argv)
	{
		mutex = va_arg(args, pthread_mutex_t *);
		pthread_mutex_unlock(mutex);
		i++;
	}
	va_end(args);
}

void	ft_status(t_philo *philo, bool reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (has_simulation_stopped(philo->table) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (DEBUG_FORMATTING == true)
	{
		write_status_debug(philo, status);
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);
}