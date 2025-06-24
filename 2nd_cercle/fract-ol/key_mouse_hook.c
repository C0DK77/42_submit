/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:08 by lgaudin           #+#    #+#             */
/*   Updated: 2025/06/07 19:27:23 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_mlx *m, int x, int y, int zoom)
{
	double	zoom_level;

	zoom_level = 1.42;
	if (zoom == 1)
	{
		m->offset_x = (x / m->zoom + m->offset_x) - (x
				/ (m->zoom * zoom_level));
		m->offset_y = (y / m->zoom + m->offset_y) - (y
				/ (m->zoom * zoom_level));
		m->zoom *= zoom_level;
	}
	else if (zoom == -1)
	{
		m->offset_x = (x / m->zoom + m->offset_x) - (x
				/ (m->zoom / zoom_level));
		m->offset_y = (y / m->zoom + m->offset_y) - (y
				/ (m->zoom / zoom_level));
		m->zoom /= zoom_level;
	}
	else
		return ;
}

void	set_random_julia(double *cx, double *cy)
{
	*cx = generate_random_c();
	*cy = generate_random_c();
}

int	key_hook(int keycode, t_mlx *m)
{
	if (keycode == ESC)
		close_program(m);
	else if (keycode == LEFT)
		m->offset_x -= 42 / m->zoom;
	else if (keycode == RIGHT)
		m->offset_x += 42 / m->zoom;
	else if (keycode == UP)
		m->offset_y -= 42 / m->zoom;
	else if (keycode == DOWN)
		m->offset_y += 42 / m->zoom;
	else if (keycode == R)
		init_mlx(m);
	else if (keycode == C)
		m->color += (255 * 255 * 255) / 100;
	else if (keycode == J)
		set_random_julia(&m->cx, &m->cx);
	else if (keycode == M || keycode == P)
		change_iterations(m, keycode);
	draw_m(m, m->name);
	return (0);
}

int	mouse_hook(int mouse_code, int x, int y, t_mlx *m)
{
	if (mouse_code == SCROLL_UP)
		zoom(m, x, y, 1);
	else if (mouse_code == SCROLL_DOWN)
		zoom(m, x, y, -1);
	draw_m(m, m->name);
	return (0);
}