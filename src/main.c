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
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#define WIDTH 900
#define HEIGHT 600

void	hook(void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fractal->mlx);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_Z))
	{ //zoom_in
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		// fractal->max_iter += get_percentage(fractal->max_iter, 10);
		fractal->x -= get_percentage(fractal->x, 30);
		fractal->_x -= get_percentage(fractal->_x, 30);
		fractal->y -= get_percentage(fractal->y, 30);
		fractal->_y -= get_percentage(fractal->_y, 30);
		draw_fractal(fractal);
		// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
		// 		fractal->y, fractal->_y);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_X))
	{ //zoom_out
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		// fractal->max_iter -= get_percentage(fractal->max_iter, 5);
		fractal->x += get_percentage(fractal->x, 30);
		fractal->_x += get_percentage(fractal->_x, 30);
		fractal->y += get_percentage(fractal->y, 30);
		fractal->_y += get_percentage(fractal->_y, 30);
		draw_fractal(fractal);
		// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
		// 		fractal->y, fractal->_y);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP))
	{ //go_up
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		fractal->y += get_percentage(fractal->y, 10);
		fractal->_y -= get_percentage(fractal->_y, 10);
		draw_fractal(fractal);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN))
	{ //go_down
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		fractal->y -= get_percentage(fractal->y, 10);
		fractal->_y += get_percentage(fractal->_y, 10);
		draw_fractal(fractal);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT))
	{ //go_left
		// fractal->img->instances[0].x -= 5;
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		fractal->x -= get_percentage(fractal->x, 10);
		fractal->_x += get_percentage(fractal->_x, 10);
		draw_fractal(fractal);
		// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
		// 		fractal->y, fractal->_y);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT))
	{ //go_right
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		fractal->x += get_percentage(fractal->x, 10);
		fractal->_x -= get_percentage(fractal->_x, 10);
		draw_fractal(fractal);
	}
	printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\nmax_iter=%d\n", fractal->x,
			fractal->_x, fractal->y, fractal->_y, fractal->max_iter);
}

float	get_percentage(float x1, float percentage)
{
	float	temp;

	temp = x1;
	temp = (x1 * percentage) / 100;
	return (temp);
}

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	remap(int value, float l1, float h1, float l2, float h2)
{
	return (l2 + (value - l1) * (h2 - l2) / (h1 - l1));
}

void	draw_fractal(t_fractal *fractal)
{
	int		color;
	float	bright;
	int		o_bright;
	float	hue;

	float zx, zy, cx, cy, tempx, z, continues_iter;
	int x, y;
	int maxx, maxy, iter;
	maxx = WIDTH;
	maxy = HEIGHT;
	mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
	for (y = 0; y < maxy; y++)
	{
		for (x = 0; x < maxx; x++)
		{
			//c_real
			// cx = remap(x, 0, WIDTH, -2.25, 0.75);
			cx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			//c_imag
			// cy = remap(y, 0, HEIGHT, -1.5, 1.5);
			cy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			//z_real
			zx = 0;
			//z_imag
			zy = 0;
			iter = 0;
			// mag = sqrt((zx*zx) + (zy * zy));
			while ((zx * zy + zy * zy) < 2 && (++iter < fractal->max_iter))
			{
				tempx = (zx * zx) - (zy * zy) + cx;
				zy = (2 * zx * zy) + cy;
				zx = tempx;
				z = (zx + zy);
				//display the created fractal
			}
			bright = remap(iter, 0, fractal->max_iter, 0, 255);
			o_bright = get_percentage(fractal->max_iter, 75);
			// if ((iter == (fractal->max_iter))
			// 	|| bright < log2(fractal->max_iter))
			if (iter == (fractal->max_iter))
			{
				// interior, part of set, black
				bright = 0;
				color = create_trgb(0, 0, 0, 0);
				mlx_put_pixel(fractal->img, x, y, 255);
			}
			else
			{
				// continues_iter = iter + 1 - log(log2(fabsf(z)));
				continues_iter = iter + 1 - (log(2) / z) / log(2);
				hue = 255 * continues_iter / fractal->max_iter;
				// hue = iter*255;
				// color = get_rgba((iter % 3) * iter * 40, (iter % 2) * iter
						// * 40,
				// 		0, 255);
				// color = create_trgb(255, bright, bright, bright);
				// color = get_rgba(bright, bright, bright, 255);
				color = get_rgba(continues_iter, hue, 0, 255);
				mlx_put_pixel(fractal->img, x, y, color);
				// memset(img->pixels, 255, img->width * img->height
				// * sizeof(int));
			}
		}
	}
	// img = mlx_new_image(mlx, x, y);
	// memset(img->pixels, 255, img->width * img->height * sizeof(int));
}

int32_t	main(void)
{
	t_fractal	fractal;

	// mlx_t	*mlx;
	fractal.y = 2.000000000000;
	fractal.x = 2.857142857143;
	fractal._y = -1 * fractal.y;
	fractal._x = -1 * fractal.x;
	fractal.max_iter = 150;
	fractal.height = HEIGHT;
	fractal.width = WIDTH;
	if (!(fractal.mlx = mlx_init(WIDTH, HEIGHT, "fract_ol", true)))
		return (EXIT_FAILURE);
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	// img->enabled = true;
	// memset(fractal.img->pixels, 255, fractal.img->width * fractal.img->height
	// * sizeof(int));
	// mlx_image_to_window(mlx, img, 5, 0);
	// fractal(-1.75, -0.25, 0.25, 0.45);
	draw_fractal(&fractal);
	// mlx_loop_hook(fractal.mlx, &hook(), fractal.mlx);
	mlx_loop_hook(fractal.mlx, &hook, &fractal);
	printf("END====\nf->x=%f\n_x=%f\ny=%f\n_y=%f\nmax_iter=%d", fractal.x,
			fractal._x, fractal.y, fractal._y, fractal.max_iter);
	mlx_loop(fractal.mlx);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
