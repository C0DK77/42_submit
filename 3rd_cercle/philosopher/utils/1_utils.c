/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:24:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/13 16:17:45 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

int64_t	ft_atoi64(char *s)
{
	int		i;
	int64_t	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
		sign = -1;
	while (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	return (res * sign);
}

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

	pthread_mutex_lock(&p->data->print_mutex);
	if (!p->data->finished)
	{
		timestamp = ft_time() - p->data->start_time;
		printf("%llu %d %s\n", timestamp, p->id, s);
	}
	pthread_mutex_unlock(&p->data->print_mutex);
}

void	ft_check_sleep(uint64_t duration_ms, t_data *d)
{
	uint64_t	start;

	start = ft_time();
	while (!d->finished && ft_time() - start < duration_ms)
		usleep(100);
}
