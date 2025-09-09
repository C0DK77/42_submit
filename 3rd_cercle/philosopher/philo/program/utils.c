/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:24:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/09 09:56:06 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

uint64_t	ft_time(void)
{
	struct timeval	tv;
	uint64_t		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
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
