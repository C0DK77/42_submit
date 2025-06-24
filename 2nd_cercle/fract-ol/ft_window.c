/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:47:36 by codk              #+#    #+#             */
/*   Updated: 2025/06/09 12:14:54 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"



int	key_hook(int keycode, t_mlx *m)
{
	if (keycode == 65307)
		close_program(m);
	return (0);
}

int	resize_hook(int x, int y, int width, int height, t_mlx *vars)
{
	(void)x;
	(void)y;
	if (width == vars->width && height == vars->height)
		return (0);
	vars->width = width;
	vars->height = height;
	mlx_destroy_image(vars->mlx, vars->image);
	vars->image = mlx_new_image(vars->mlx, width, height);
	vars->p = mlx_get_data_addr(vars->image, &vars->bits, &vars->line_size,
			&vars->endian);
	draw_fractal(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image, 0, 0);
	return (0);
}

void	my_pixel_put(t_mlx *v, int x, int y, int color)
{
	char	*dst;

	dst = v->p + (y * v->line_size + x * (v->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_fractal(t_mlx *v)
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
			while (z_re * z_re + z_im * z_im <= 4.0 && iter < v->max_iterations)
			{
				tmp = z_re * z_re - z_im * z_im + c_re;
				z_im = 2.0 * z_re * z_im + c_im;
				z_re = tmp;
				iter++;
			}
			color = (iter == v->max_iterations) ? 0x000000 : (iter * 0xFFFFFF
					/ v->max_iterations);
			my_pixel_put(v, x, y, color);
		}
	}
}

int	expose_hook(t_mlx *vars)
{
	draw_fractal(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image, 0, 0);
	return (0);
}
