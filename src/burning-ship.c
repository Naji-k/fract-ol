/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   burning-ship.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 22:25:41 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/09 22:25:41 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	burning_ship_iteration(t_fractal *fractal, double zx, double zy,
		int *iter)
{
	double	tempx;
	double	p_zx;
	double	p_zy;

	p_zx = zx * zx;
	p_zy = zy * zy;
	while ((p_zx + p_zy) < 4 && (*iter <= fractal->max_iter))
	{
		p_zx = zx * zx;
		p_zy = zy * zy;
		tempx = p_zx - p_zy + fractal->cx;
		zy = fabs(2 * zx * zy) + fractal->cy;
		zx = fabs(tempx);
		*iter = *iter + 1;
	}
}

void	draw_burning_ship(t_fractal *fractal)
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
			iter = 0;
			burning_ship_iteration(fractal, zx, zy, &iter);
			color_fractal(fractal, iter, x, y);
		}
	}
}
