#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <stdlib.h>

# define WIDTH 700
# define HEIGH 700
# define THREAD_WIDTH 7
# define THREAD_NUMBER 100
# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define R 15
# define C 8
# define H 4
# define J 38
# define P 35
# define M 46
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
	char	*p;
	int		bits;
	int		line_size;
	int		endian;
	double	re_min;
	double	re_max;
	double	im_min;
	double	im_max;
	int		max_iterations;

	int		x;
	int		y;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	int		color;
	double	offset_x;
	double	offset_y;
}			t_mlx;

int			key_hook(int keycode, t_mlx *m);
int			close_program(t_mlx *m);
int			resize_hook(int x, int y, int width, int height, t_mlx *m);
void		draw_fractal(t_mlx *m);
void		my_pixel_put(t_mlx *m, int x, int y, int color);
int			expose_hook(t_mlx *m);

#endif
