/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractal_sets.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/07 18:07:02 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/07 18:07:02 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	color_fractal(t_fractal *fractal, int iter, int x, int y)
{
	int		color;
	double	continues_iter;

	if (iter == (fractal->max_iter + 1))
		mlx_put_pixel(fractal->img, x, y, 255);
	else
	{
		continues_iter = iter + 1 / log(2);
		color = get_rgba(continues_iter, iter * fractal->color, iter
				* fractal->color * 11, 255);
		mlx_put_pixel(fractal->img, x, y, color);
	}
}

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
			zx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			zy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			iter = 1;
			julia_set_iteration(fractal, zx, zy, &iter);
			color_fractal(fractal, iter, x, y);
		}
	}
}

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
			//z_real
			zx = 0;
			//z_imag
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