/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:35:50 by lgaudin           #+#    #+#             */
/*   Updated: 2025/06/08 11:56:47 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

void	*draw_mandelbrot(void *m_void)
{
	t_mlx	*m;

	m = (t_mlx *)m_void;
	m->x = 0;
	m->y = 0;
	while (m->x < WIDTH)
	{
		while (m->y < HEIGH)
		{
			calculate_mandelbrot(m);
			m->y++;
		}
		m->x++;
		m->y = 0;
	}
	return (NULL);
}

void	draw_julia(t_mlx *m)
{
	m->x = 0;
	m->y = 0;
	while (m->x < WIDTH)
	{
		while (m->y < HEIGH)
		{
			calculate_julia(m);
			m->y++;
		}
		m->x++;
		m->y = 0;
	}
}

// void	draw_burning_ship(t_mlx *m)
// {
// 	m->x = 0;
// 	m->y = 0;
// 	while (m->x < WIDTH)
// 	{
// 		while (m->y < HEIGH)
// 		{
// 			calculate_burning_ship(m);
// 			m->y++;
// 		}
// 		m->x++;
// 		m->y = 0;
// 	}
// }

void	calculate_julia(t_mlx *m)
{
	int		i;
	double	tmp;

	m->name = "julia";
	m->zx = m->x / m->zoom + m->offset_x;
	m->zy = m->y / m->zoom + m->offset_y;
	i = 0;
	while (++i < m->max_iterations)
	{
		tmp = m->zx;
		m->zx = m->zx * m->zx - m->zy * m->zy + m->cx;
		m->zy = 2 * m->zy * tmp + m->cy;
		if (m->zx * m->zx + m->zy * m->zy >= __DBL_MAX__)
			break ;
	}
	if (i == m->max_iterations)
		put_color_to_pixel(m, m->x, m->y, 0x000000);
	else
		put_color_to_pixel(m, m->x, m->y, (m->color * i));
}

void	calculate_mandelbrot(t_mlx *m)
{
	int i;
	double x_temp;

	m->name = "mandel";
	i = 0;
	m->zx = 0.0;
	m->zy = 0.0;
	m->cx = (m->x / m->zoom) + m->offset_x;
	m->cy = (m->y / m->zoom) + m->offset_y;
	while (++i < m->max_iterations)
	{
		x_temp = m->zx * m->zx - m->zy * m->zy + m->cx;
		m->zy = 2. * m->zx * m->zy + m->cy;
		m->zx = x_temp;
		if (m->zx * m->zx + m->zy * m->zy >= __DBL_MAX__)
			break ;
	}
	if (i == m->max_iterations)
		put_color_to_pixel(m, m->x, m->y, 0x000000);
	else
		put_color_to_pixel(m, m->x, m->y, (m->color * i));
}