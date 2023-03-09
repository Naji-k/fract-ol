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

void	draw_burning_ship(t_fractal *fractal)
{
	double zx, zy, tempx;
	int x, y;
	int iter;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			// fractal->cx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			fractal->cx =  fractal->_x + x * fractal->re_factor;
			// fractal->cy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			fractal->cy =  fractal->_y + y * fractal->im_factor;
			zx = 0;
			zy = 0;
			iter = 0;
			while (((zx * zx) + (zy * zy)) < 4 && (++iter <= fractal->max_iter))
			{
				tempx = powf(zx, 2) - powf(zy, 2) + fractal->cx;
				zy = fabs(2 * zx * zy) + fractal->cy;
				zx = fabs(tempx);
			}
			color_fractal(fractal, iter, x, y);
		}
	}
}
