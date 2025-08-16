/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:24:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 12:42:15 by corentindes      ###   ########.fr       */
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

	pthread_mutex_lock(&p->data->print);
	if (!p->data->finished)
	{
		timestamp = ft_time() - p->data->start_time;
		printf("%llu %d %s\n", timestamp, p->id, s);
	}
	pthread_mutex_unlock(&p->data->print);
}

void	ft_check_sleep(uint64_t duration_ms, t_data *d)
{
	uint64_t	start;

	start = ft_time();
	while (!d->finished && ft_time() - start < duration_ms)
		usleep(100);
}
