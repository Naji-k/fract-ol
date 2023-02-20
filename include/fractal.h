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

typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		width;
	double		height;
	double		y;
	double		_y;
	double		x;
	double		_x;
	int			max_iter;
}				t_fractal;

float			remap(int value, float l1, float h1, float l2, float h2);
int				create_trgb(int t, int r, int g, int b);
int	get_rgba(int r, int g, int b, int a); //mlx42
void			draw_fractal(t_fractal *fractal);
float		 	get_percentage(float x1, float percentage);

#endif