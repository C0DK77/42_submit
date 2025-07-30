/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:24:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/30 15:08:15 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

int64_t	ft_atoi_int64(char *s)
{
	int		i;
	int64_t	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	return (res * sign);
}

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	print_action(t_philo *p, char *msg)
{
	uint64_t	timestamp;

	pthread_mutex_lock(&p->data->print_mutex);
	if (!p->data->finished)
	{
		timestamp = get_time() - p->data->start_time;
		printf("%llu %d %s\n", timestamp, p->id, msg);
	}
	pthread_mutex_unlock(&p->data->print_mutex);
}
