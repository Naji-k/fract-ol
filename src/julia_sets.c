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
	double	p_zx;
	double	p_zy;

	p_zx = zx * zx;
	p_zy = zy * zy;
	while ((p_zx + p_zy) < 8 && (*iter <= fractal->max_iter))
	{
		p_zx = zx * zx;
		p_zy = zy * zy;
		tempx = (p_zx) - (p_zy) + fractal->cx;
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
			zx = remap(x, WIDTH, fractal->_x, fractal->x);
			zy = remap(y, HEIGHT, fractal->_y, fractal->y);
			iter = 1;
			julia_set_iteration(fractal, zx, zy, &iter);
			color_fractal(fractal, iter, x, y);
		}
	}
}
