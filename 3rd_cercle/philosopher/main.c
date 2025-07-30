/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:18:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/30 16:18:45 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "philosopher.h"

int	main(int argc, char **argv)
{
	int i;
	t_data *d;
	i = 0;
	d = malloc(sizeof(t_data));
	if (!d)
		return (1);
	if (!check_args(argc, argv))
		return (1);
	variables_data_init(argc, argv, d);
	if (!variables_philos_init(d))
		return (1);
	if (!thread_init(d))
		return (1);

	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor, d);
	pthread_join(monitor_thread, NULL);
	while (i < d->nb)
	{
		pthread_join(d->philos[i].thread, NULL);
		i++;
	}

	free_data(d);
	return (0);
}