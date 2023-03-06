/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractal_moves.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 18:33:18 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/01 18:33:18 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	move_up(t_fractal *fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.001;
	fractal->y += fractal->offset;
	fractal->_y += fractal->offset;
	// re_factor(fractal);
	run_fractal(fractal);
}

void	move_down(t_fractal *fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.0001;
	fractal->y -= fractal->offset;
	fractal->_y -= fractal->offset;
	// fractal->height = fractal->height * 0.95;
	// re_factor(fractal);
	// draw_fractal_mandelbrot(fractal);
	run_fractal(fractal);
}

void	move_left(t_fractal *fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.001;
	// fractal->img->instances[0].x -= 5;
	fractal->x += fractal->offset;
	fractal->_x += fractal->offset;
	// draw_fractal_mandelbrot(fractal);
	run_fractal(fractal);
	// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
	// 		fractal->y, fractal->_y);
}

void	move_right(t_fractal *fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.001;
	// fractal->offset = remap(t, 0, WIDTH, fractal->_x, fractal->x);
	fractal->x -= fractal->offset;
	fractal->_x -= fractal->offset;
	// re_factor(fractal);
	run_fractal(fractal);
}

void	reset_defaults(t_fractal *fractal)
{
	fractal->width = WIDTH;
	fractal->height = HEIGHT;
	// fractal->y = 1.5;
	fractal->_y = -4;
	fractal->_x = -4;
	fractal->x = 4;
	fractal->y = 4;
	fractal->scale_x = fabsl(fractal->x) + fabsl(fractal->_x);
	fractal->scale_y = fabsl(fractal->y) + fabsl(fractal->_y);
	// fractal->y = fractal->_y + (fractal->x - fractal->_x) * (fractal->height
	// / fractal->width);
	fractal->zoom = 1;
	fractal->r = 2;
	// re_factor(fractal);
	fractal->max_iter = 64;
	fractal->zoom_level = 1;
	fractal->offset = 0.025;
	fractal->height = HEIGHT;
	fractal->width = WIDTH;
	fractal->color = 10;
}
