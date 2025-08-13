/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:18:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/13 16:18:24 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

int	main(int ac, char **av)
{
	int			i;
	t_data 		*d;
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
		pthread_join(d->philos[i].thread, NULL);
		i++;
	}
	ft_free_data(d);
	return (0);
}