/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractal_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/07 16:46:59 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/07 16:46:59 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	run_fractal(t_fractal *fractal)
{
	render_fractal_set(fractal->set, fractal);
}

void	render_fractal_set(const char set, t_fractal *fractal)
{
	static const t_fractal_set_list	fractal_set[256] = {
	['M'] = draw_fractal_mandelbrot,
	['J'] = draw_julia_set,
	['B'] = draw_burning_ship,
	};

	if (fractal_set[(int)set])
		fractal_set[(int)set](fractal);
}

int	shuffle_color(int value)
{
	if (value <= 250)
		value += 30;
	else if (value > 250)
		value -= 20;
	return (value);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
