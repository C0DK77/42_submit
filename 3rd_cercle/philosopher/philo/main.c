/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:18:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/23 05:54:09 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*d;

	d = NULL;
	if (!ft_check_av(ac, av))
		return (1);
	d = ft_init_var_data(ac, av);
	if (!d)
		return (1);
	if (!ft_start_philo(d))
		return (1);
	ft_stop_philo(d);
	return (0);
}
