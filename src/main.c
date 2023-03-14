/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/14 22:47:07 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/02/14 22:47:07 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	my_key_func(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractal->mlx);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		fractal->color = shuffle_color(fractal->color);
	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
		reset_defaults(fractal);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		fractal->set = 'M';
	if (keydata.key == MLX_KEY_B && keydata.action == MLX_PRESS)
		fractal->set = 'B';
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		fractal->max_iter++;
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		fractal->max_iter--;
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
		show_hide_help(fractal);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		fractal->scheme = change_color_scheme(fractal->scheme);
	run_fractal(fractal);
}

void	my_scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (ydelta > 0)
	{
		get_mouse_position(fractal);
		apply_zoom(fractal, fractal->mouse->m_re, fractal->mouse->m_im, 1.05);
		fractal->zoom_level--;
	}
	else if (ydelta < 0)
	{
		get_mouse_position(fractal);
		apply_zoom(fractal, fractal->mouse->m_re, fractal->mouse->m_im, 0.97);
		fractal->zoom_level++;
	}
	if (xdelta < 0)
		puts("Sliiiide to the left!");
	else if (xdelta > 0)
		puts("Sliiiide to the right!");
	run_fractal(fractal);
}

void	my_hook(void *param)
{
	t_fractal	*fractal;
	t_mouse		*mouse;

	fractal = param;
	mouse = fractal->mouse;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_J))
	{
		fractal->set = 'J';
		mlx_get_mouse_pos(fractal->mlx, &mouse->pos_x, &mouse->pos_y);
		fractal->cx = remap(mouse->pos_x, WIDTH, fractal->_x, fractal->x);
		fractal->cy = remap(mouse->pos_y, HEIGHT, fractal->y, fractal->_y);
		run_fractal(fractal);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP))
		move_down(fractal);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN))
		move_up(fractal);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT))
		move_left(fractal);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT))
		move_right(fractal);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;
	t_mouse		mouse;

	fractal.mouse = &mouse;
	reset_defaults(&fractal);
	if (check_input(argc, argv, &fractal))
		return (EXIT_SUCCESS);
	fractal.mlx = mlx_init(WIDTH, HEIGHT, "fract_ol", true);
	if (!fractal.mlx)
		return (EXIT_FAILURE);
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
	run_fractal(&fractal);
	txt_on_screen(&fractal);
	mlx_scroll_hook(fractal.mlx, &my_scroll_hook, &fractal);
	mlx_loop_hook(fractal.mlx, &my_hook, &fractal);
	mlx_key_hook(fractal.mlx, my_key_func, &fractal);
	mlx_loop(fractal.mlx);
	return (EXIT_SUCCESS);
}
