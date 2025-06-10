/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:21:02 by codk              #+#    #+#             */
/*   Updated: 2025/06/10 03:47:05 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_mlx	m;

	if ((argc == 2 && ft_strcmp(argv[1], "julia") != 0) || (argc == 4
			&& ft_strcmp(argv[1], "julia") == 0))
	{
		m.mlx = mlx_init();
		m.window = mlx_new_window(m.mlx, WIDTH, HEIGHT, "Fract-ol");
		m.image.mlx_image = mlx_new_image(m.mlx, WIDTH, HEIGHT);
		m.image.p = mlx_get_data_addr(m.image.mlx_image, &m.image.bits,
				&m.image.line_size, &m.image.endian);
		init_program(&m.image.fractal);
		set_fractal_name(argv, &m.image.fractal);
		mlx_loop_hook(m.mlx, &render_fractal, &m);
		mlx_mouse_hook(m.window, &mouse_event, &m);
		mlx_key_hook(m.window, &key_event, &m);
		mlx_hook(m.window, 17, 0, close_program, &m);
		mlx_loop(m.mlx);
		return (0);
	}
	else if (argc != 4 && ft_strcmp(argv[1], "julia") == 0)
		ft_putstr("You must add coordinates for Julia in your arguments");
	else
		ft_putstr("You must enter a fractal\nmandelbrot | julia | Burningship\n");
	return (0);
}
