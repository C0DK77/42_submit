/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:54:33 by cdesjars          #+#    #+#             */
/*   Updated: 2025/06/10 03:43:30 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <stdlib.h>

# define WIDTH 700
# define HEIGHT 700
# define ZOOM 1.5
# define ESC 32
# define UP 65364
# define DOWN 65362
# define LEFT 65361
# define RIGHT 65363
# define R 114
# define MINUS 45
# define PLUS 61
# define K_1 49
# define K_2 50
# define K_3 51
# define K_4 52
# define K_5 53
# define K_6 54
# define K_7 55
# define K_8 56
# define K_9 57
# define C 99
# define SCROLL_UP 4
# define SCROLL_DOWN 5

# define WHITE 0xFFFFFF
# define GREY 0x808080
# define PURPLE 0x800080
# define BLUE 0xFF
# define GREEN 0x006400
# define YELLOW 0xFFFF00
# define BROWN 0x964B00
# define PINK 0xFFC0CB
# define RED 0xFF0000
# define ORANGE 0xFFA500
# define BLK 0x00

typedef struct s_fractal
{
	double		scale;
	double		movex;
	double		movey;
	double		re_const;
	double		im_const;
	int			max;
	char		type;
	int			color;
	int			color_shift;
}				t_fractal;

typedef struct s_draw
{
	void		*mlx_image;
	char		*p;
	int			bits;
	int			line_size;
	int			endian;
	t_fractal	fractal;
}				t_draw;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_draw		image;
}				t_mlx;

//	EVENTS

void			manage_iterations(int code, t_fractal *f);
void			manage_color(int code, t_fractal *f);
int				key_event(int code, t_mlx *m, t_fractal *f);
int				mouse_event(int code, int x, int y, t_mlx *m);
void			put_color_to_pixel(t_draw *d, int x, int y, int color);

//	FRACTALS

void			fractal(t_draw *d);
void			draw(int x, int y, t_draw *d);
int				mandelbrot(double c1, double c2, t_fractal *f);
int				julia(double c1, double c2, t_fractal *f);
int				burning_ship(double c1, double c2, t_fractal *f);

//	PROGRAM

void			init_program(t_fractal *f);
void			set_fractal_name(char **av, t_fractal *f);
void			print_infos(t_mlx *m);
int				render_fractal(t_mlx *m);
int				close_program(t_mlx *m);

//	UTILS
int				ft_is_in_plan(double x, double y, int i, t_fractal *f);
double			ft_parse_digits(const char **ps, int *e);
double			ft_atoi_double(const char *s);
int				ft_power(int b, int i);
double			ft_fabs(double n);

#endif
