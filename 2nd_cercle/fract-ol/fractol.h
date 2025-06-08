/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:54:33 by cdesjars          #+#    #+#             */
/*   Updated: 2025/06/08 11:57:12 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <stdlib.h>

# define WIDTH 700
# define HEIGH 700
# define ZOOM 1.42
# define ESC 32
# define UP 65364
# define DOWN 65362
# define LEFT 65361
# define RIGHT 65363
# define R 114
# define C 99
# define H 104
# define J 106
# define P 112
# define M 109
# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct s_mlx
{
	void	*mlx;
	char	*name;
	void	*window;
	void	*image;
	int		color;
	double	zoom;
	void	*p;
	int		bits;
	int		line_size;
	int		endian;
	int		x;
	int		y;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	double	offset_x;
	double	offset_y;
	int		max_iterations;
}			t_mlx;

void		init_fractal(t_mlx *m);
void		init_mlx(t_mlx *m);
int			draw_fractal(t_mlx *m, char *argv);
int			close_program(t_mlx *m);
int			key_event(int key_code, t_mlx *m);
int			mouse_event(int mouse_code, int x, int y, t_mlx *m);
void		zoom(t_mlx *m, int x, int y, int zoom);
double		generate_random_c(void);
void		put_color_to_pixel(t_mlx *m, int x, int y, int color);
void		change_iterations(t_mlx *m, int code);
void		*draw_mandelbrot(void *m_void);
void		draw_julia(t_mlx *m);
void		draw_burning_ship(t_mlx *m);
void		calculate_julia(t_mlx *m);
void		calculate_mandelbrot(t_mlx *m);

#endif
