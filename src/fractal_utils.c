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
	static const t_fractal_set_list fractal_set[256] = {
		['M'] = draw_fractal_mandelbrot,
		['J'] = draw_julia_set,
		['B'] = draw_burning_ship,
	};
	if (fractal_set[(int)set])
		fractal_set[(int)set](fractal);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	show_hide_help(t_fractal *fractal)
{
	if (fractal->help % 2)
	{
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
		txt_on_screen(fractal);
	}
	else
	{
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
		mlx_put_string(fractal->mlx, "H:Show menu", 10, 740);
	}
	run_fractal(fractal);
	fractal->help++;
}