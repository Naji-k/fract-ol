/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia_sets.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/07 18:07:02 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/07 18:07:02 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"


void	julia_set_iteration(t_fractal *fractal, double zx, double zy, int *iter)
{
	double	tempx;

	while (((zx * zx) + (zy * zy)) < 4 * fractal->x
		&& (*iter <= fractal->max_iter))
	{
		tempx = (zx * zx) - (zy * zy) + fractal->cx;
		zy = (2 * zx * zy) + fractal->cy;
		zx = tempx;
		*iter = *iter + 1;
	}
}

void	draw_julia_set(t_fractal *fractal)
{
	int		iter;
	int		x;
	int		y;
	double	zx;
	double	zy;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			// zx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			zx =  fractal->_x + x * fractal->re_factor;
			zy = fractal->_y + y * fractal->im_factor;
			iter = 1;
			julia_set_iteration(fractal, zx, zy, &iter);
			color_fractal(fractal, iter, x, y);
		}
	}
}
