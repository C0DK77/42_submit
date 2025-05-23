#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	double	re_min;
	double	re_max;
	double	im_min;
	double	im_max;
	int		max_iter;
}			t_vars;

int			key_hook(int keycode, t_vars *vars);
int			close_program(t_vars *vars);
int			resize_hook(int x, int y, int width, int height, t_vars *vars);
void		draw_fractal(t_vars *v);
void		my_pixel_put(t_vars *v, int x, int y, int color);
int			expose_hook(t_vars *vars);

#endif
