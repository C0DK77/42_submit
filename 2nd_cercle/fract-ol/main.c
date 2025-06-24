/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:21:02 by codk              #+#    #+#             */
/*   Updated: 2025/06/09 12:13:08 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

int	main(void)
{
	t_mlx	vars;

	vars.width = 800;
	vars.height = 600;
	vars.re_min = -2.0;
	vars.re_max = 1.0;
	vars.im_min = -1.2;
	vars.im_max = 1.2;
	vars.max_iterations = 100;
	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, vars.width, vars.height, "fract'ol");
	vars.image = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.p = mlx_get_data_addr(vars.image, &vars.bits, &vars.line_size,
			&vars.endian);
	draw_fractal(&vars);
	mlx_put_image_to_window(vars.mlx, vars.window, vars.image, 0, 0);
	mlx_hook(vars.window, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.window, 17, 0L, close_program, &vars);
	mlx_expose_hook(vars.window, expose_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
//

int	draw_fractal(t_mlx *fractal, char *query)
{
	if (ft_strncmp(query, "mandel", 7) == 0)
		draw_mandelbrot(fractal);
	else if (ft_strncmp(query, "julia", 6) == 0)
	{
		if (!fractal->cx && !fractal->cy)
		{
			fractal->cx = -0.745429;
			fractal->cy = 0.05;
		}
	draw_julia(fractal);
}
else if (ft_strncmp(query, "ship", 5) == 0)
	draw_burning_ship(fractal);
else
{
	ft_putendl_fd("Available fractals: mandel, julia, ship", 1);
	exit_fractal(fractal);
}
mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0,
	0);
return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*fractal;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fractol <fractal>", 1);
		ft_putendl_fd("Available fractals: mandelbrot, julia, burningship", 1);
		return (0);
	}
	fractal = malloc(sizeof(t_mlx));
	init_fractal(fractal);
	init_mlx(fractal);
	mlx_key_hook(fractal->window, key_hook, fractal);
	mlx_mouse_hook(fractal->window, mouse_hook, fractal);
	mlx_hook(fractal->window, 17, 0L, exit_fractal, fractal);
	draw_fractal(fractal, argv[1]);
	mlx_loop(fractal->mlx);
	return (0);
}