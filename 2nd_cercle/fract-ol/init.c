/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:58:57 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/08 11:08:28 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

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

void	init_mlx(t_mlx *m)
{
	m->mlx = mlx_init();
	m->window = mlx_new_window(m->mlx, WIDTH, HEIGH, "Fract-ol");
	m->image = mlx_new_image(m->mlx, WIDTH, HEIGH);
	m->p = mlx_get_data_addr(m->image, &m->bits, &m->line_size, &m->endian);
}

int	draw_fractal(t_mlx *m, char *argv)
{
	if (ft_strcmp(argv, "mandel") == 0)
		draw_mandelbrot(m);
	else if (ft_strcmp(argv, "julia") == 0)
	{
		if (!m->cx && !m->cy)
		{
			m->cx = -0.745429;
			m->cy = 0.05;
		}
		draw_julia(m);
	}
	// else if (ft_strncmp(argv, "ship", 5) == 0)
	// 	draw_burning_ship(m);
	else
	{
		ft_putstr("Available ms: mandel, julia, ship");
		close_program(m);
	}
	mlx_put_image_to_window(m->mlx, m->window, m->image, 0,
		0);
	return (0);
}

int	close_program(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->image);
	mlx_destroy_window(m->mlx, m->window);
	free(m->mlx);
	free(m);
	exit(1);
}