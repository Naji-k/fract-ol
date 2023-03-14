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
	fractal->y -= fractal->offset;
	fractal->_y -= fractal->offset;
	run_fractal(fractal);
}

void	move_down(t_fractal *fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.0001;
	fractal->y += fractal->offset;
	fractal->_y += fractal->offset;
	run_fractal(fractal);
}

void	move_left(t_fractal *fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.001;
	fractal->x += fractal->offset;
	fractal->_x += fractal->offset;
	run_fractal(fractal);
}

void	move_right(t_fractal *fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.001;
	fractal->x -= fractal->offset;
	fractal->_x -= fractal->offset;
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
	fractal->cx = 0;
	fractal->cy = -1;
	fractal->max_iter = 64;
	fractal->zoom_level = 1;
	fractal->offset = 0.025;
	fractal->color = 10;
	fractal->scheme = 0;
}
