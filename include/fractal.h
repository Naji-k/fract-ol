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

typedef struct s_screen
{
}				t_screen;
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
	double long	y;
	double long	_y;
	double long	x;
	double long	_x;
	double		re_factor;
	double		im_factor;
	int			max_iter;
	int			color;
}				t_fractal;

float			remap(int value, float l1, float h1, float l2, float h2);
int				create_trgb(int t, int r, int g, int b);
int	get_rgba(int r, int g, int b, int a); //mlx42
void			draw_fractal_mandelbrot(t_fractal *fractal);
float			get_percentage(float x1, float percentage);
void			re_factor(t_fractal *fractal);

#endif