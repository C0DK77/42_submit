/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:58:57 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/10 03:48:54 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

void	init_program(t_fractal *f)
{
	f->scale = 1.0;
	f->movex = 0.0;
	f->movey = 0.0;
	f->max = 400;
	f->re_const = 0.0;
	f->im_const = 0.0;
	f->color = GREEN;
	f->color_shift = 0;
}

void	set_fractal_name(char **argv, t_fractal *f)
{
	if (!ft_strcmp(argv[1], "julia"))
	{
		f->type = 'j';
		f->re_const = ft_atoi_double(argv[2]);
		f->im_const = ft_atoi_double(argv[3]);
	}
	if (!ft_strcmp(argv[1], "mandelbrot"))
		f->type = 'm';
	if (!ft_strcmp(argv[1], "burningship"))
		f->type = 'b';
}

void	print_infos(t_mlx *m)
{
	mlx_string_put(m->mlx, m->window, 20, 60, WHITE, "Colors: 1 - 9");
	mlx_string_put(m->mlx, m->window, 20, 90, WHITE, "Iterations: + / -");
	mlx_string_put(m->mlx, m->window, 20, 120, WHITE, "Color Shift: C");
}

int	render_fractal(t_mlx *m)
{
	if (m->image.fractal.color_shift)
	{
		m->image.fractal.color += 5000;
		if (m->image.fractal.color > 0xFFFFFF)
			m->image.fractal.color = 1;
	}
	fractal(&m->image);
	mlx_put_image_to_window(m->mlx, m->window, m->image.mlx_image, 0, 0);
	print_infos(m);
	return (0);
}

int	close_program(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->image.mlx_image);
	mlx_destroy_window(m->mlx, m->window);
	mlx_destroy_display(m->mlx);
	mlx_loop_end(m->mlx);
	free(m->mlx);
	exit(1);
	return (0);
}
