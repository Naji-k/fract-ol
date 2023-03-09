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

void	draw_fractal_mandelbrot(t_fractal *fractal)
{
	int		color;
	double zx, zy, tempx;
	int x, y;
	int iter;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			fractal->cx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			// fractal->cx = fractal->_x + x * fractal->re_factor;
			fractal->cy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			// fractal->cy = fractal->y - y * fractal->im_factor;
			zx = 0;
			zy = 0;
			iter = 1;
			while (((zx * zx) + (zy * zy)) < 4 && (++iter <= fractal->max_iter))
			{
				tempx = (zx * zx) - (zy * zy) + fractal->cx;
				zy = (2 * zx * zy) + fractal->cy;
				zx = tempx;
			}
			if (iter == (fractal->max_iter + 1))
				mlx_put_pixel(fractal->img, x, y, 255);
			else
			{
				color = get_rgba((iter) , (iter) * 30 , iter * 20 , 255);
				mlx_put_pixel(fractal->img, x, y, color);
			}
		}
	}
}
