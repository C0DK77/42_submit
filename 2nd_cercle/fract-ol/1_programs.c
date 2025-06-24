/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_programs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:58:57 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/07 19:26:41 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractal(t_mlx *m)
{
	m->x = 0;
	m->y = 0;
	m->color = 0xFCBE11;
	m->zoom = 300;
	m->offset_x = -1.21;
	m->offset_y = -1.21;
	m->max_iterations = 42;
}

void	init_mlx(t_mlx *fractal)
{
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, WIDTH, HEIGH, "Fract-ol");
	fractal->image = mlx_new_image(fractal->mlx, WIDTH, HEIGH);
	fractal->p = mlx_get_data_addr(fractal->image, &fractal->bits,
			&fractal->line_size, &fractal->endian);
}

int	close_program(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->image);
	mlx_destroy_window(m->mlx, m->window);
	free(m->mlx);
	free(m);
	exit(1);
	return (0);
}