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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void my_key_func(mlx_key_data_t keydata, void* param)
{
	t_fractal	*fractal;

	fractal = param;
	
	if (keydata.key == MLX_KEY_ESCAPE  && keydata.action == MLX_PRESS)
	{
		mlx_close_window(fractal->mlx);
	}
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
/* 	if (keydata.key == MLX_KEY_DOWN  && keydata.action == MLX_PRESS)
	{ //go_down
		move_up(fractal);
	}
	if (keydata.key == MLX_KEY_UP  && keydata.action == MLX_PRESS)
	{ //go_up
		move_down(fractal);
	}
	if (keydata.key == MLX_KEY_LEFT  && keydata.action == MLX_PRESS)
	{ //go_left
		move_left(fractal);
	}
	if (keydata.key == MLX_KEY_RIGHT  && keydata.action == MLX_PRESS)
	{ //go_right
		move_right(fractal);
	} */
	if (keydata.key == MLX_KEY_C  && keydata.action == MLX_PRESS)
	{//c change color
		fractal->color = shuffle_color(fractal->color);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_D  && keydata.action == MLX_PRESS)
	{//D print debugging
		printf("f->x=%Lf\n_x=%Lf\ny=%Lf\n_y=%Lf\nmax_iter=%d\nfra.w=%f\n,fra.h=%f\nre_fac=%f\nim_fac=%f\nzoom=%f\n,zoom_level=%f\n", fractal->x,
			fractal->_x, fractal->y, fractal->_y, fractal->max_iter,fractal->width,fractal->height, fractal->re_factor, fractal->im_factor, fractal->zoom,fractal->zoom_level);
	}
	if (keydata.key ==MLX_KEY_P  && keydata.action == MLX_PRESS)
	{
		double X,Y;
		double perX,perY;
		mlx_get_mouse_pos(fractal->mlx, &fractal->pos_x, &fractal->pos_y);
		
		// X = fractal->pos_x / fractal->width  * 100.0;
		X = remap(fractal->pos_x,0,WIDTH,0,fractal->x - fractal->_x);
		Y = remap(fractal->pos_y,0,HEIGHT,fractal->y,fractal->_y);
		// fractal->cx = X;
		// fractal->cy = Y;
		perX = X/ 4 * 100;
		perY = Y / 4 * 100;
		printf("screen.x=%d\nscreen.y=%d\nX_trans=%f\nY_trans=%f\nperX=%f\n,perY=%f\n",fractal->pos_x,fractal->pos_y,X,Y,perX,perY);
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
		move_X_percentage(fractal,20);
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

void mouse_percentage(t_fractal* fractal)
{
	int X,Y;

	mlx_get_mouse_pos(fractal->mlx, &fractal->pos_x, &fractal->pos_y);
	X = fractal->pos_x / fractal->width * 100;
	Y = fractal->pos_y / fractal->height * 100;
	move_percentage(fractal,X);
	printf("X=%d\tY=%d\n",X,Y);
}


void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (ydelta > 0)
	{
		// double X;
		// double Y;
		// double perX;
		// double perY;
		// zoom_on_screen(fractal,'I');
		// zoom_on_value(fractal,'I');
		zoom_with_factor (fractal, 'I');

		// mlx_get_mouse_pos(fractal->mlx, &fractal->pos_x, &fractal->pos_y);
		// X = remap(fractal->pos_x,0,WIDTH,0,4);
		// Y = remap(fractal->pos_y,0,HEIGHT,fractal->y,fractal->_y);
		// perX = X/ 4 * 100;
		// perY = Y / 4 * 100;
		// move_X_percentage(fractal,perX);
		// move_Y_percentage(fractal,perY);
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


float	get_percentage(float x1, float percentage)
{
	float	temp;

	temp = x1;
	temp = (x1 * percentage) / 100;
	return (temp);
}

float	remap(int value, float l1, float h1, float l2, float h2)
{
	return (l2 + (value - l1) * (h2 - l2) / (h1 - l1));
//			 re_min + (x) * (re_max - re_min) / (width)
}

float	distance(int x1, int y1, int x2, int y2)
{
	int	res;
	res = sqrt((x2 - x1) * (x2 - x1) + ((y2 - y1) * (y2 - y1)));
	return (res);
}

void re_factor (t_fractal *fractal)
{
	fractal->re_factor = (fractal->x - fractal->_x)  * fractal->zoom / (fractal->width);
	fractal->im_factor = (fractal->y - fractal->_y)  * fractal->zoom / (fractal->height) ;
	// printf("re_fac=%f\nim_fac=%f",fractal->re_factor, fractal->im_factor);
}

void	draw_fractal_mandelbrot(t_fractal *fractal)
{
	int		color;
	double zx, zy, tempx;
	double continues_iter, mag;
	int x, y;
	int iter;
	x = -1;
	fractal->r = -1 * (WIDTH - fractal->width);
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			//c_real
			// fractal->cx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			fractal->cx = fractal->_x + x * fractal->re_factor;
			// fractal->cx = (x - fractal->width) / (fractal->zoom * fractal->width);
			//c_imag
			// fractal->cy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			fractal->cy = fractal->y - y * fractal->im_factor;
			// fractal->cy = (y - fractal->height) / (fractal->zoom * fractal->height);
			//z_real
			zx = 0;
			//z_imag
			zy = 0;
			iter = 1;
			while (((zx * zx) + (zy * zy)) < 4 && (++iter <= fractal->max_iter))
			{
				tempx = (zx * zx) - (zy * zy) + fractal->cx;
				zy = (2 * zx * zy) + fractal->cy;
				zx = tempx;
			}
			if (iter == (fractal->max_iter + 1))
				mlx_put_pixel(fractal->img, x, y, 255);
			else
			{
				mag = sqrt((zx * zx) + (zy * zy));
				// mu = iter - (log (log (mag))) / log(2);
				continues_iter = iter + 1 - (log(2) / fabs(mag)) / log(2);
				// color = get_rgba((iter % 3) * iter , (iter % 2) * iter * 40,
				// 		100, 255);
				// color = create_trgb(255, bright, bright, bright);
				// color = get_rgba(100, 50, 200, 255);
				color = get_rgba(continues_iter, iter * fractal->color, iter * fractal->color * 11, 255);
				mlx_put_pixel(fractal->img, x, y, color);
			}
		}
	}
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
		mlx_put_string(fractal.mlx,"C:change color mod",10,600);
		mlx_put_string(fractal.mlx,"=:iteration++",10,620);
		mlx_put_string(fractal.mlx,"-:iteration--",10,640);
		mlx_put_string(fractal.mlx,"J:Julia",10,660);
		mlx_put_string(fractal.mlx,"M:Mandelbrot",10,680);
		mlx_put_string(fractal.mlx,"B:Burning-Ship",10,700);

		mlx_scroll_hook(fractal.mlx, &my_scrollhook ,&fractal);
		mlx_loop_hook(fractal.mlx, &my_hook, &fractal);
		mlx_key_hook(fractal.mlx,my_key_func,&fractal);
		mlx_loop(fractal.mlx);
		// mlx_terminate(fractal.mlx);
		return (EXIT_SUCCESS);
}