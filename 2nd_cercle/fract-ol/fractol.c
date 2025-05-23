/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:21:02 by codk              #+#    #+#             */
/*   Updated: 2025/05/22 21:17:08 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

int	main(void)
{
	t_vars	vars;

	vars.width = 800;
	vars.height = 600;
	vars.re_min = -2.0;
	vars.re_max = 1.0;
	vars.im_min = -1.2;
	vars.im_max = 1.2;
	vars.max_iter = 100;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "fract'ol");
	vars.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bpp, &vars.line_len,
			&vars.endian);
	draw_fractal(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0L, close_program, &vars);
	mlx_expose_hook(vars.win, expose_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
