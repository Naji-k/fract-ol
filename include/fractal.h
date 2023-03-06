/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractal.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 23:19:52 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/02/15 23:19:52 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "./MLX42/MLX42.h"
# include <math.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

typedef struct s_fractal
{
	mlx_t		*mlx;
	int32_t		pos_x;
	int32_t		pos_y;
	mlx_image_t	*img;
	double		width;
	double		height;
	double		offset;
	double		zoom_level;
	double		zoom;
	double long	y;
	double long	_y;
	double long	x;
	double long	_x;
	double long	r;
	double		cx;
	double		cy;
	double		re_factor;
	double		im_factor;
	int			max_iter;
	int			color;
	char		set;
	double long	scale_x;
	double long	scale_y;
}				t_fractal;
typedef struct s_screen
{
	float		offset_x;
	float		offset_y;
}				t_screen;

typedef void	(*t_fractal_set_list)(t_fractal *fractal);

float			remap(int value, float l1, float h1, float l2, float h2);
int				create_trgb(int t, int r, int g, int b);
int				get_rgba(int r, int g, int b, int a); //mlx42
void			re_factor(t_fractal *fractal);
void			draw_fractal_mandelbrot(t_fractal *fractal);
float			get_percentage(float x1, float percentage);
void			draw_julia_set(t_fractal *fractal);
void			draw_burning_ship(t_fractal *fractal);
void			run_fractal(t_fractal *fractal);
//moves
void			move_up(t_fractal *fractal);
void			move_down(t_fractal *fractal);
void			move_left(t_fractal *fractal);
void			move_right(t_fractal *fractal);
void			reset_defaults(t_fractal *fractal);
void			my_hook(void *param);
double			ft_atof(const char *arr);
#endif