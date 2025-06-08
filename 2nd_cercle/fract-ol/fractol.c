/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:21:02 by codk              #+#    #+#             */
/*   Updated: 2025/06/08 11:42:32 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_mlx *m;

	if (argc != 2)
	{
		ft_putstr("You must enter a fractal: mandelbrot, julia");
		return (0);
	}
	m = malloc(sizeof(t_mlx));
	init_fractal(m);
	init_mlx(m);
	mlx_key_hook(m->window, key_event, m);
	mlx_mouse_hook(m->window, mouse_event, m);
	mlx_hook(m->window, 17, 0L, close_program, m);
	draw_fractal(m, argv[1]);
	mlx_loop(m->mlx);
	return (0);
}