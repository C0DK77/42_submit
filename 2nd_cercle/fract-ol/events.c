/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:08 by lgaudin           #+#    #+#             */
/*   Updated: 2025/06/10 03:49:14 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

void	manage_color(int code, t_fractal *f)
{
	if (code == K_1)
		f->color = GREY;
	if (code == K_2)
		f->color = PURPLE;
	if (code == K_3)
		f->color = BLUE;
	if (code == K_4)
		f->color = WHITE;
	if (code == K_5)
		f->color = YELLOW;
	if (code == K_6)
		f->color = BROWN;
	if (code == K_7)
		f->color = PINK;
	if (code == K_8)
		f->color = RED;
	if (code == K_9)
		f->color = ORANGE;
}

void	manage_iterations(int code, t_fractal *f)
{
	if (code == MINUS)
	{
		if (f->max > 100)
			f->max /= 2;
	}
	if (code == PLUS)
	{
		if (f->max < 1000)
			f->max *= 2;
	}
}

int	key_event(int code, t_mlx *m, t_fractal *f)
{
	if (code == ESC)
		close_program(m);
	else if (code == LEFT)
		f->movex += 0.5 * 1 / f->scale;
	else if (code == RIGHT)
		f->movex -= 0.5 * 1 / f->scale;
	else if (code == UP)
		f->movey += 0.5 * 1 / f->scale;
	else if (code == DOWN)
		f->movey -= 0.5 * 1 / f->scale;
	else if (code == C)
		m->image.fractal.color += (255 * 255 * 255) / 100;
	manage_iterations(code, &m->image.fractal);
	manage_color(code, &m->image.fractal);
	return (0);
}

int	mouse_event(int code, int x, int y, t_mlx *m)
{
	double	old_scale;
	double	new_scale;
	double	mouse_re;
	double	mouse_im;

	mouse_re = (x - WIDTH / 2.0) * 4.0 / WIDTH / m->image.fractal.scale
		+ m->image.fractal.movex;
	mouse_im = (y - HEIGHT / 2.0) * 4.0 / WIDTH / m->image.fractal.scale
		+ m->image.fractal.movey;
	old_scale = m->image.fractal.scale;
	if (code == SCROLL_UP)
		new_scale = old_scale * 1.5;
	else if (code == SCROLL_DOWN)
		new_scale = old_scale / 1.5;
	else
		return (0);
	m->image.fractal.scale = new_scale;
	m->image.fractal.movex = mouse_re - (x - WIDTH / 2.0) * 4.0 / WIDTH
		/ new_scale;
	m->image.fractal.movey = mouse_im - (y - HEIGHT / 2.0) * 4.0 / WIDTH
		/ new_scale;
	return (0);
}

void	put_color_to_pixel(t_draw *d, int x, int y, int color)
{
	char	*c;

	c = d->p + (y * d->line_size + x * (d->bits / 8));
	*(int *)c = color;
}
