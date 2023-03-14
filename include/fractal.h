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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

typedef struct s_mouse
{
	int32_t		pos_x;
	int32_t		pos_y;
	double		m_re;
	double		m_im;
}				t_mouse;

typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_mouse		*mouse;
	double		width;
	double		height;
	double		offset;
	double		zoom_level;
	double long	y;
	double long	_y;
	double long	x;
	double long	_x;
	double		cx;
	double		cy;
	int			max_iter;
	int			color;
	int			scheme;
	char		set;
	int			help;
}				t_fractal;

typedef void	(*t_fractal_set_list)(t_fractal *fractal);
//parsing_inputs
int				check_input(int argc, char **argv, t_fractal *fractal);
double			ft_atof(const char *arr);
void			print_available_fractals(const char **fractals);

float			remap(int value, float h1, float l2, float h2);

void			re_factor(t_fractal *fractal);
//draw fractals
void			draw_fractal_mandelbrot(t_fractal *fractal);
void			draw_julia_set(t_fractal *fractal);
void			draw_burning_ship(t_fractal *fractal);
void			run_fractal(t_fractal *fractal);
void			render_fractal_set(const char set, t_fractal *fractal);
//coloring
int				get_rgba(int r, int g, int b, int a);
int				coloring(t_fractal *fractal, int iter);
void			color_fractal(t_fractal *fractal, int iter, int x, int y);
int				change_color_scheme(int color_number);
int				shuffle_color(int value);
//help menu
void			show_hide_help(t_fractal *fractal);
void			txt_on_screen(t_fractal *fractal);
//moves
void			move_up(t_fractal *fractal);
void			move_down(t_fractal *fractal);
void			move_left(t_fractal *fractal);
void			move_right(t_fractal *fractal);
void			reset_defaults(t_fractal *fractal);
void			my_hook(void *param);
void			mouse_percentage(t_fractal *fractal);
void			move_percentage(t_fractal *fractal, int percentage);
void			move_X_percentage(t_fractal *fractal, float percentage);
void			move_Y_percentage(t_fractal *fractal, float percentage);
//zoom
void			get_mouse_position(t_fractal *fractal);
void			apply_zoom(t_fractal *fractal, double mouse_re, double mouse_im,
					double zoom_factor);
double			interpolate(double start, double end, double interpolate);
#endif