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
	fractal->y += fractal->zoom / 2;
	fractal->_y += fractal->zoom / 2;
	re_factor(fractal);
	run_fractal(fractal);
}

void	move_down(t_fractal *fractal)
{
	// if (fractal->zoom_level >= 50)
	// 	fractal->offset = 0.005;
	// else if (fractal->zoom_level >= 150)
	// 	fractal->offset = 0.0001;
	fractal->y -= fractal->zoom / 2;
	fractal->_y -= fractal->zoom / 2;
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
	fractal->x += fractal->zoom / 2;
	fractal->_x += fractal->zoom /2;
	// draw_fractal_mandelbrot(fractal);
	re_factor(fractal);
	run_fractal(fractal);
	// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
	// 		fractal->y, fractal->_y);
}

void	move_right(t_fractal *fractal)
{
	// if (fractal->zoom_level >= 50)
	// 	fractal->offset = 0.005;
	// else if (fractal->zoom_level >= 150)
	// 	fractal->offset = 0.001;
	// fractal->offset = remap(t, 0, WIDTH, fractal->_x, fractal->x);
	fractal->x -= fractal->zoom / 2;
	fractal->_x -= fractal->zoom / 2;
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
	// fractal->y = 2;
	fractal->scale_x = fabsl(fractal->x) + fabsl(fractal->_x);
	fractal->scale_y = fabsl(fractal->y) + fabsl(fractal->_y);
	fractal->y = fractal->_y + (fractal->x - fractal->_x) * (fractal->height
	/ fractal->width);
	fractal->zoom = 1;
	fractal->r = 2;
	fractal->cx = 0;
	fractal->cy = -1;
	re_factor(fractal);
	fractal->max_iter = 64;
	fractal->zoom_level = 1;
	fractal->offset = 0.025;
	fractal->height = HEIGHT;
	fractal->width = WIDTH;
	fractal->color = 10;
}

void zoom_on_screen(t_fractal *fractal, char in_out)
{
	if (in_out == 'O')
	{
		fractal->height = fractal->height * 0.95;
		fractal->width = fractal->width * 0.95;
		fractal->zoom_level -= 1;
	} else {
		fractal->height = fractal->height * 1.05;
		fractal->width = fractal->width * 1.05;
		fractal->zoom_level += 1;
	}
}

void	zoom_on_value(t_fractal *fractal, char in_out)
{
	if (in_out == 'O')
	{
		fractal->x  = fractal->x  * 1.05;
		fractal->_x  = fractal->_x * 1.05;
		fractal->y  = fractal->y * 1.05;
		fractal->_y  = fractal->_y * 1.05;
		fractal->zoom_level +=1;
	}
	else {
		fractal->x  = fractal->x  * 0.95;
		fractal->_x  = fractal->_x * 0.95;
		fractal->y  = fractal->y * 0.95;
		fractal->_y  = fractal->_y * 0.95;
		fractal->zoom_level -=1;
	}
	re_factor(fractal);
}

void	move_percentage(t_fractal *fractal, int percentage)
{
	if (percentage > 50)
	{
		fractal->x -= get_percentage(fractal->x, percentage);
		fractal->_x += get_percentage(fractal->_x, percentage);
	}
	else
	{
		fractal->x += get_percentage(fractal->x, percentage);
		fractal->_x -= get_percentage(fractal->_x, percentage);
	}
}

void move_X_percentage(t_fractal* fractal, float percentage)
{
	// float _percentage = 100 - percentage;
	if (percentage < 50.0)
	{
		fractal->_x += fractal->_x * (percentage / 100);
		fractal->x -= fractal->x * (percentage / 100);
	}
	// re_factor(fractal);
}
void move_Y_percentage(t_fractal* fractal, float percentage)
{
	float scaleY = 2;
	scaleY *= percentage / 100;
	fractal->y -= scaleY;
	fractal->_y -= scaleY;
}

void zoom_with_factor (t_fractal *fractal, char in_out)
{
	if (in_out == 'O')
	{
		fractal->zoom *= 1.05;
		fractal->zoom_level++;
		re_factor(fractal);
		// run_fractal(fractal);
	}
	else
	{
		fractal->zoom *= 0.95;
		fractal->zoom_level++;
		re_factor(fractal);
		// run_fractal(fractal);	
	}
}