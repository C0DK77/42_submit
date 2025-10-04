/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:18:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/04 04:14:11 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_data	*d;

	d = NULL;
	if (!ft_check_av(ac, av))
		return (1);
	d = ft_init_var_data(ac, av, 1);
	if (!d)
		return (0);
	if (!ft_init_var_philo(d))
		return (0);
	if (!ft_init_thread(d))
		return (0);
	if (!ft_start_philo(d))
		return (EXIT_FAILURE);
	ft_stop_philo(d);
	return (0);
}
