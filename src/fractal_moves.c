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
	// if (fractal->zoom_level >= 50)
	// 	fractal->offset = 0.005;
	// else if (fractal->zoom_level >= 150)
	// 	fractal->offset = 0.001;
	fractal->y += fractal->zoom ;
	fractal->_y += fractal->zoom;
	re_factor(fractal);
	run_fractal(fractal);
}

void	move_down(t_fractal *fractal)
{
	// if (fractal->zoom_level >= 50)
	// 	fractal->offset = 0.005;
	// else if (fractal->zoom_level >= 150)
	// 	fractal->offset = 0.0001;
	fractal->y -= fractal->zoom ;
	fractal->_y -= fractal->zoom ;
	re_factor(fractal);
	run_fractal(fractal);
}

void	move_left(t_fractal *fractal)
{
	// if (fractal->zoom_level >= 50)
	// 	fractal->offset = 0.005;
	// else if (fractal->zoom_level >= 150)
	// 	fractal->offset = 0.001;
	// fractal->img->instances[0].x -= 5;
	fractal->x += fractal->zoom;
	fractal->_x += fractal->zoom ;
	re_factor(fractal);
	run_fractal(fractal);
}

void	move_right(t_fractal *fractal)
{
	// if (fractal->zoom_level >= 50)
	// 	fractal->offset = 0.005;
	// else if (fractal->zoom_level >= 150)
	// 	fractal->offset = 0.001;
	// fractal->offset = remap(t, 0, WIDTH, fractal->_x, fractal->x);
	fractal->x -= fractal->zoom ;
	fractal->_x -= fractal->zoom ;
	re_factor(fractal);
	run_fractal(fractal);
}

void	reset_defaults(t_fractal *fractal)
{
	fractal->width = WIDTH;
	fractal->height = HEIGHT;
	fractal->_y = -2;
	fractal->_x = -2;
	fractal->x = 2;
	fractal->y = 2;
	fractal->scale_x = fabsl(fractal->x) + fabsl(fractal->_x);
	fractal->scale_y = fabsl(fractal->y) + fabsl(fractal->_y);
	// fractal->y = fractal->_y + (fractal->x - fractal->_x) * (fractal->height
	// 		/ fractal->width);
	fractal->zoom = 1;
	fractal->cx = 0;
	fractal->cy = -1;
	re_factor(fractal);
	fractal->max_iter = 64;
	fractal->zoom_level = 1;
	fractal->offset = 0.025;
	fractal->color = 10;
	fractal->scheme = 0;
}

void	zoom_on_screen(t_fractal *fractal, char in_out)
{
	if (in_out == 'O')
	{
		fractal->height = fractal->height * 0.95;
		fractal->width = fractal->width * 0.95;
		fractal->zoom_level -= 1;
	}
	else
	{
		fractal->height = fractal->height * 1.05;
		fractal->width = fractal->width * 1.05;
		fractal->zoom_level += 1;
	}
}

void	zoom_on_value(t_fractal *fractal, char in_out)
{
	if (in_out == 'O')
	{
		fractal->x = fractal->x * 1.05;
		fractal->_x = fractal->_x * 1.05;
		fractal->y = fractal->y * 1.05;
		fractal->_y = fractal->_y * 1.05;
		fractal->zoom *= 1.05;
		fractal->zoom_level += 1;
	}
	else
	{
		fractal->x = fractal->x * 0.95;
		fractal->_x = fractal->_x * 0.95;
		fractal->y = fractal->y * 0.95;
		fractal->_y = fractal->_y * 0.95;
		fractal->zoom *= 0.95;
		fractal->zoom_level -= 1;
	}
	re_factor(fractal);
}

void	zoom_with_factor(t_fractal *fractal, char in_out)
{
	if (in_out == 'O')
	{
		fractal->zoom *= 1.1;
		fractal->zoom_level++;
	}
	else
	{
		fractal->zoom *= 0.99;
		fractal->zoom_level++;
	}
	re_factor(fractal);
}