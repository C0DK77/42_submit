/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:08 by lgaudin           #+#    #+#             */
/*   Updated: 2025/06/08 11:55:04 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

int	key_event(int code, t_mlx *m)
{
	printf("key pressed: %d\n", code);
	if (code == ESC)
		close_program(m);
	else if (code == LEFT)
		m->offset_x -= 42 / m->zoom;
	else if (code == RIGHT)
		m->offset_x += 42 / m->zoom;
	else if (code == UP)
		m->offset_y -= 42 / m->zoom;
	else if (code == DOWN)
		m->offset_y += 42 / m->zoom;
	else if (code == R)
		init_mlx(m);
	else if (code == C)
		m->color += (255 * 255 * 255) / 100;
	else if (code == J)
	{
		m->cx = generate_random_c();
		m->cy = generate_random_c();
	}
	else if (code == M || code == P)
		change_iterations(m, code);
	draw_fractal(m, m->name);
	return (0);
}

int	mouse_event(int code, int x, int y, t_mlx *m)
{
	if (code == SCROLL_UP)
		zoom(m, x, y, 1);
	else if (code == SCROLL_DOWN)
		zoom(m, x, y, -1);
	draw_fractal(m, m->name);
	return (0);
}

void	zoom(t_mlx *m, int x, int y, int zoom)
{
	if (zoom == 1)
	{
		m->offset_x = (x / m->zoom + m->offset_x) - (x / (m->zoom * ZOOM));
		m->offset_y = (y / m->zoom + m->offset_y) - (y / (m->zoom * ZOOM));
		m->zoom *= ZOOM;
	}
	else if (zoom == -1)
	{
		m->offset_x = (x / m->zoom + m->offset_x) - (x / (m->zoom / ZOOM));
		m->offset_y = (y / m->zoom + m->offset_y) - (y / (m->zoom / ZOOM));
		m->zoom /= ZOOM;
	}
	else
		return ;
}

void	change_iterations(t_mlx *m, int code)
{
	if (code == M)
	{
		if (m->max_iterations > 42)
			m->max_iterations -= 42;
	}
	else if (code == P)
	{
		if (m->max_iterations < 42)
				m->max_iterations += 42;
	}
}

double	generate_random_c(void)
{
	return (((double)rand() / RAND_MAX) * 3.0 - 1.5);
}

void	put_color_to_pixel(t_mlx *m, int x, int y, int color)
{
	int	*buffer;

	buffer = m->p;
	buffer[(y * m->line_size / 4) + x] = color;
}