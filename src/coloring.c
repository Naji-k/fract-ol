/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coloring.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 16:20:08 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/09 16:20:08 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	coloring(t_fractal *fractal, int iter)
{
	int	color;
	int	value;

	value = fractal->color;
	if (fractal->scheme == 1)
		color = get_rgba(iter * value, iter, iter, 255);
	else if (fractal->scheme == 2)
		color = get_rgba(iter, iter * value, iter, 255);
	else if (fractal->scheme == 3)
		color = get_rgba(iter, iter, iter * value, 255);
	else if (fractal->scheme == 4)
		color = get_rgba(iter * fractal->color, iter * fractal->color, iter
				* fractal->color, 255);
	else
		color = get_rgba(iter + fractal->color, (iter) * fractal->color, iter
				* fractal->color * 11, 255);
	return (color);
}

void	color_fractal(t_fractal *fractal, int iter, int x, int y)
{
	int	color;

	if (iter == (fractal->max_iter + 1))
		mlx_put_pixel(fractal->img, x, y, 255);
	else
	{
		color = coloring(fractal, iter);
		mlx_put_pixel(fractal->img, x, y, color);
	}
}

int	shuffle_color(int value)
{
	if (value <= 1000)
		value += 20;
	else if (value > 1000)
		value /= 30;
	return (value);
}

int	change_color_scheme(int color_number)
{
	if (color_number > 4)
		color_number = 0;
	color_number++;
	return (color_number);
}
