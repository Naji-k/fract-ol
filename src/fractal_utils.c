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

float	remap(int value, float h1, float l2, float h2)
{
	float	l1;

	l1 = 0;
	return (l2 + (value - l1) * (h2 - l2) / (h1 - l1));
}

void	run_fractal(t_fractal *fractal)
{
	mlx_delete_image(fractal->mlx, fractal->img);
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
	render_fractal_set(fractal->set, fractal);
	txt_on_screen(fractal);
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
		mlx_put_string(fractal->mlx, "H: Show menu", 10, 760);
	}
	run_fractal(fractal);
	fractal->help++;
}

void	txt_on_screen(t_fractal *fractal)
{
	if (fractal->help % 2)
	{
		mlx_put_string(fractal->mlx, "Arrows: to move", 10, 600);
		mlx_put_string(fractal->mlx, "C: change colors", 10, 620);
		mlx_put_string(fractal->mlx, "S: change color scheme", 10, 640);
		mlx_put_string(fractal->mlx, "=/- =iteration (+/-)", 10, 660);
		mlx_put_string(fractal->mlx, "J:Julia", 10, 680);
		mlx_put_string(fractal->mlx, "M: Mandelbrot", 10, 700);
		mlx_put_string(fractal->mlx, "B: Burning-Ship", 10, 720);
		mlx_put_string(fractal->mlx, "0: Reset", 10, 740);
		mlx_put_string(fractal->mlx, "H: Hide menu", 10, 760);
	}
	else
		mlx_put_string(fractal->mlx, "H: Show menu", 10, 760);
}
