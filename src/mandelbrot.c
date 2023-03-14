/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandelbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 02:32:03 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/09 02:32:03 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	mandelbrot_iteration(t_fractal *fractal, double zx, double zy,
		int *iter)
{
	double	tempx;

	while (((zx * zx) + (zy * zy)) < 4 && (*iter <= fractal->max_iter))
	{
		tempx = (zx * zx) - (zy * zy) + fractal->cx;
		zy = (2 * zx * zy) + fractal->cy;
		zx = tempx;
		*iter = *iter + 1;
	}
}

void	draw_fractal_mandelbrot(t_fractal *fractal)
{
	int		iter;
	double	zx;
	double	zy;
	int		x;
	int		y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			fractal->cx = remap(x, fractal->width, fractal->_x, fractal->x);
			fractal->cy = remap(y, fractal->height, fractal->_y, fractal->y);
			zx = 0;
			zy = 0;
			iter = 1;
			mandelbrot_iteration(fractal, zx, zy, &iter);
			color_fractal(fractal, iter, x, y);
		}
	}
}
