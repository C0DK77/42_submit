/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:24:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/07 04:15:33 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

uint64_t	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_action(t_philo *p, char *s, int i)
{
	pthread_mutex_lock(&p->data->print);
	if (ft_monitor_check_stop_flag(p->data) == 1 && i == 0)
	{
		pthread_mutex_unlock(&p->data->print);
		return ;
	}
	printf(TIME "%lu \033[0m %d %s\n", ft_time() - p->data->start_time, p->id
		+ 1, s);
	pthread_mutex_unlock(&p->data->print);
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

void	ft_mutex_unlock_all(int argv, ...)
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
