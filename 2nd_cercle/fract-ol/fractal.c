/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 00:06:06 by cdesjars          #+#    #+#             */
/*   Updated: 2025/06/10 02:32:51 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

int	burning_ship(double c1, double c2, t_fractal *f)
{
	int		i;
	double	x;
	double	y;
	double	t;

	x = 0.0;
	y = 0.0;
	t = 0.0;
	i = 0;
	while (ft_is_in_plan(x, y, i, f))
	{
		t = ft_fabs(x) * ft_fabs(x) - ft_fabs(y) * ft_fabs(y) + c1;
		y = 2 * ft_fabs(x) * ft_fabs(y) + c2;
		x = t;
		i++;
	}
	return (i);
}

int	julia(double c1, double c2, t_fractal *f)
{
	int		i;
	double	x;
	double	y;
	double	t;

	x = c1;
	y = c2;
	t = 0.0;
	i = 0;
	while (ft_is_in_plan(x, y, i, f))
	{
		t = x * x - y * y + f->re_const;
		y = 2 * x * y + f->im_const;
		x = t;
		i++;
	}
	return (i);
}

int	mandelbrot(double c1, double c2, t_fractal *f)
{
	int		i;
	double	x;
	double	y;
	double	t;

	x = 0.0;
	y = 0.0;
	t = 0.0;
	i = 0;
	while (ft_is_in_plan(x, y, i, f))
	{
		t = x * x - y * y + c1 - 0.3;
		y = 2 * x * y + c2;
		x = t;
		i++;
	}
	return (i);
}

void	draw(int x, int y, t_draw *d)
{
	double	c_re;
	double	c_im;
	int		i;

	i = 0;
	c_re = ((y - WIDTH / 2.0) * 4.0 / WIDTH) * (1 / (d->fractal.scale))
		+ d->fractal.movex;
	c_im = ((x - HEIGHT / 2.0) * 4.0 / WIDTH) * (1 / d->fractal.scale)
		+ d->fractal.movey;
	if (d->fractal.type == 'm')
		i = mandelbrot(c_re, c_im, &d->fractal);
	if (d->fractal.type == 'j')
		i = julia(c_re, c_im, &d->fractal);
	if (d->fractal.type == 'b')
		i = burning_ship(c_re, c_im, &d->fractal);
	if (i < d->fractal.max)
		put_color_to_pixel(d, y, x, d->fractal.color * i / (d->fractal.max
				/ 20));
	else
		put_color_to_pixel(d, y, x, BLK);
}

void	fractal(t_draw *d)
{
	int	x;
	int	y;

	x = 0;
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			draw(x, y, d);
			y++;
		}
		x++;
	}
}
