/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_zoom.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:50:04 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/14 16:50:04 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	get_mouse_position(t_fractal *fractal)
{
	t_mouse	*mouse_pos;

	mouse_pos = fractal->mouse;
	mlx_get_mouse_pos(fractal->mlx, &mouse_pos->pos_x, &mouse_pos->pos_y);
	mouse_pos->m_re = remap(mouse_pos->pos_x, WIDTH, fractal->_x, fractal->x);
	mouse_pos->m_im = remap(mouse_pos->pos_y, HEIGHT, fractal->_y, fractal->y);
}

double	interpolate(double start, double end, double interpolate)
{
	return (start + ((end - start) * interpolate));
}

void	apply_zoom(t_fractal *fractal, double mouse_re, double mouse_im,
		double zoom_factor)
{
	fractal->_x = interpolate(mouse_re, fractal->_x, zoom_factor);
	fractal->x = interpolate(mouse_re, fractal->x, zoom_factor);
	fractal->_y = interpolate(mouse_im, fractal->_y, zoom_factor);
	fractal->y = interpolate(mouse_im, fractal->y, zoom_factor);
}
