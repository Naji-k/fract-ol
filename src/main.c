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

void my_key_func(mlx_key_data_t keydata, void* param)
{
	t_fractal	*fractal;

	fractal = param;
	
	if (keydata.key == MLX_KEY_ESCAPE  && keydata.action == MLX_PRESS)
		mlx_close_window(fractal->mlx);
 	if (keydata.key == MLX_KEY_Z  && keydata.action == MLX_PRESS)
	{
		// zoom_on_value(fractal,'I');
		fractal->zoom *= 0.95;
		// fractal->zoom_level++;
		// fractal->y = fractal->y * 0.95;
		// fractal->_y = fractal->_y * 0.95;
		// fractal->x = fractal->x * 0.95;
		// fractal->_x = fractal->_x * 0.95;
		re_factor(fractal);
		run_fractal(fractal);

		// printf("f->x=%Lf\n_x=%Lf\ny=%Lf\n_y=%Lf\nZ_level=%f\n", fractal->x, fractal->_x,
		// 	fractal->y, fractal->_y, fractal->zoom_level);
		// printf("width=%f\nhight=%f\n",fractal->width, fractal->height);
	}
	if (keydata.key == MLX_KEY_X  && keydata.action == MLX_PRESS)
	{ //zoom_out
		// zoom_on_value(fractal, 'O');
		fractal->zoom *= 1.05;
		// fractal->y -= fractal->y * 1.05;
		// fractal->_y -= fractal->_y * 1.05;
		// fractal->x -= fractal->x * 1.05;
		// fractal->_x -= fractal->_x * 1.05;
		fractal->zoom_level--;
		re_factor(fractal);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_C  && keydata.action == MLX_PRESS)
	{
		fractal->color = shuffle_color(fractal->color);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_D  && keydata.action == MLX_PRESS)
	{
		printf("f->x=%Lf\n_x=%Lf\ny=%Lf\n_y=%Lf\nmax_iter=%d\nfra.w=%f\n,fra.h=%f\nre_fac=%f\nim_fac=%f\nzoom=%f\n,zoom_level=%f\n", fractal->x,
			fractal->_x, fractal->y, fractal->_y, fractal->max_iter,fractal->width,fractal->height, fractal->re_factor, fractal->im_factor, fractal->zoom,fractal->zoom_level);
	}

	if (keydata.key == MLX_KEY_0  && keydata.action == MLX_PRESS)
	{
		reset_defaults(fractal);
		// re_factor(fractal);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_T  && keydata.action == MLX_PRESS)
	{
		// mouse_percentage(fractal);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_M  && keydata.action == MLX_PRESS)
	{
		fractal->set = 'M';
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_B  && keydata.action == MLX_PRESS)
	{
		fractal->set = 'B';
		run_fractal(fractal);
	}
	if(keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	{
		fractal->max_iter++;
		run_fractal(fractal);
	}
	if(keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
	{
		fractal->max_iter--;
		run_fractal(fractal);
	}
}


void	my_scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (ydelta > 0)
	{
		// zoom_on_screen(fractal,'I');
		// zoom_on_value(fractal,'I');
		zoom_with_factor (fractal, 'I');
		run_fractal(fractal);
	}
	else if (ydelta < 0)
	{
		// zoom_on_screen(fractal,'O');
		// zoom_on_value(fractal,'O');
		zoom_with_factor (fractal, 'O');
		run_fractal(fractal);
	}
	if (xdelta < 0)
		puts("Sliiiide to the left!");
	else if (xdelta > 0)
		puts("Sliiiide to the right!");
}


float	remap(int value, float l1, float h1, float l2, float h2)
{
	return (l2 + (value - l1) * (h2 - l2) / (h1 - l1));
}


void re_factor (t_fractal *fractal)
{
	fractal->re_factor = (fractal->x - fractal->_x)  * fractal->zoom / (fractal->width);
	fractal->im_factor = (fractal->y - fractal->_y)  * fractal->zoom / (fractal->height);
}


void	my_hook(void *param)
{
	t_fractal*	fractal;
	float	X;
	float	Y;
	fractal = param;

	if (mlx_is_key_down(fractal->mlx, MLX_KEY_J))
	{
		fractal->set = 'J';
		mlx_get_mouse_pos(fractal->mlx,&fractal->pos_x,&fractal->pos_y);
		X = remap(fractal->pos_x,0,WIDTH,fractal->_x,fractal->x) ;
		Y = remap(fractal->pos_y,0,HEIGHT,fractal->y,fractal->_y);
		fractal->cx = X;
		fractal->cy = Y;
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

void txt_on_screen(t_fractal* fractal)
{
	mlx_put_string(fractal->mlx, "C=change color mod", 10, 600);
	mlx_put_string(fractal->mlx, "=:iteration++", 10, 620);
	mlx_put_string(fractal->mlx, "-:iteration--", 10, 640);
	mlx_put_string(fractal->mlx, "J:Julia", 10, 660);
	mlx_put_string(fractal->mlx, "M:Mandelbrot", 10, 680);
	mlx_put_string(fractal->mlx, "B:Burning-Ship", 10, 700);
	mlx_put_string(fractal->mlx, "0: Reset", 10, 720);
}

int	main(int argc, char** argv)
{
	t_fractal	fractal;
	char *fractals_set[] = {"Mandelbrot", "Julia", "Burning-Ship"};

	reset_defaults(&fractal);
	if (check_input(argc, argv, fractals_set, &fractal))
		return(EXIT_SUCCESS);
	if (!(fractal.mlx = mlx_init(WIDTH, HEIGHT, "fract_ol",true)))
			return (EXIT_FAILURE);
		fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
		mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
		run_fractal(&fractal);
		txt_on_screen(&fractal);
		mlx_scroll_hook(fractal.mlx, &my_scroll_hook ,&fractal);
		mlx_loop_hook(fractal.mlx, &my_hook, &fractal);
		mlx_key_hook(fractal.mlx,my_key_func,&fractal);
		mlx_loop(fractal.mlx);
		// mlx_terminate(fractal.mlx);
		return (EXIT_SUCCESS);
}
