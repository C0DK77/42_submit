/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:18:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/03 19:12:09 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	int			i;
	t_data		*d;
	pthread_t	monitor_thread;

	i = 0;
	d = malloc(sizeof(t_data));
	if (!d)
		return (1);
	if (!ft_check_av(ac, av))
		return (1);
	ft_init_var_data(ac, av, d);
	if (!ft_init_var_philo(d))
		return (1);
	if (!ft_init_thread(d))
		return (1);
	pthread_create(&monitor_thread, NULL, monitor, d);
	pthread_join(monitor_thread, NULL);
	while (i < d->nb)
	{
		pthread_join(d->philo[i].thread, NULL);
		i++;
	}
	ft_free_data(d);
	return (0);
}

int64_t	ft_atoi64(char *s)
{
	int64_t	res;
	int		sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		sign = -1;
	while (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
	{
		res = (res * 10) + (*s - '0');
		s++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (47 < c && c < 58)
		return (1);
	return (0);
}
