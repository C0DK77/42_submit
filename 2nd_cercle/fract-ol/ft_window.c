/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:47:36 by codk              #+#    #+#             */
/*   Updated: 2025/05/22 21:17:43 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_program(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_program(vars);
	return (0);
}

int	resize_hook(int x, int y, int width, int height, t_vars *vars)
{
	(void)x;
	(void)y;
	if (width == vars->width && height == vars->height)
		return (0);
	vars->width = width;
	vars->height = height;
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, width, height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->line_len,
			&vars->endian);
	draw_fractal(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

void	my_pixel_put(t_vars *v, int x, int y, int color)
{
	char	*dst;

	dst = v->addr + (y * v->line_len + x * (v->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_fractal(t_vars *v)
{
	double	c_re;
	double	c_im;
	double	z_re;
	double	z_im;
	int		iter;
	double	tmp;
	int		color;

	int x, y;
	for (y = 0; y < v->height; y++)
	{
		for (x = 0; x < v->width; x++)
		{
			c_re = v->re_min + (double)x * (v->re_max - v->re_min) / v->width;
			c_im = v->im_max - (double)y * (v->im_max - v->im_min) / v->height;
			z_re = 0.0;
			z_im = 0.0;
			iter = 0;
			while (z_re * z_re + z_im * z_im <= 4.0 && iter < v->max_iter)
			{
				tmp = z_re * z_re - z_im * z_im + c_re;
				z_im = 2.0 * z_re * z_im + c_im;
				z_re = tmp;
				iter++;
			}
			color = (iter == v->max_iter) ? 0x000000 : (iter * 0xFFFFFF
					/ v->max_iter);
			my_pixel_put(v, x, y, color);
		}
	}
}

int	expose_hook(t_vars *vars)
{
	draw_fractal(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}
