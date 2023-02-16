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
#define WIDTH 800
#define HEIGHT 800
#define MAX_ITER 64

void	hook(void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fractal->mlx);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP))
	{
		mlx_delete_image(fractal->mlx, fractal->img);
		fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
		// fractal->img->instances[0].y -= 5;
		fractal->x = decrease_percentage(fractal->x, 30);
		fractal->_x = decrease_percentage(fractal->_x, 30);
		fractal->y = decrease_percentage(fractal->y, 30);
		fractal->_y = -1 * fractal->y;
		draw_fractal(fractal);
		printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
				fractal->y, fractal->_y);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN))
		fractal->img->instances[0].y += 5;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT))
		fractal->img->instances[0].x -= 5;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT))
		fractal->img->instances[0].x += 5;
}

float	decrease_percentage(float x1, float percentage)
{
	float	temp;

	temp = x1;
	temp -= (x1 * percentage) / 100;
	return (temp);
}
/* void	draw(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		while (y < HEIGHT)
		{
			y++;
		}
		x++;
	}
} */
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
	int	color;

	float zx, zy, cx, cy, tempx;
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
			cx = remap(x, 0, WIDTH, fractal->_x, fractal->x);
			// cx = remap(x, 0, WIDTH, -1.575, 0.525);
			// cx = remap(x, 0, WIDTH, -1.1025, 0.3675);
			//c_imag
			// cy = remap(y, 0, HEIGHT, -1.5, 1.5);
			cy = remap(y, 0, HEIGHT, fractal->_y, fractal->y);
			// cy = remap(y, 0, HEIGHT, -1.05, 1.05);	//30%
			// cy = remap(y, 0, HEIGHT, -0.735, 0.735);	//30%
			//z_real
			zx = 0;
			//z_imag
			zy = 0;
			iter = 1;
			// mag = sqrt((zx*zx) + (zy * zy));
			while (sqrt((zx * zy + zy * zy)) < 4 && (iter < MAX_ITER))
			{
				tempx = (zx * zx) - (zy * zy) + cx;
				zy = (2 * zx * zy) + cy;
				zx = tempx;
				iter++;
				//display the created fractal
			}
			int bright = remap(iter, 0 ,MAX_ITER,0,255);
			if ((iter == MAX_ITER) || bright < 20)
			{
			bright = 0;		
				// color = create_trgb(0, 0, 0, 20);
				color = create_trgb(bright,bright,bright,255);
				mlx_put_pixel(fractal->img, x, y, color);
			}
			else
			{
				// color = create_trgb((iter % 3) * iter * 40, (iter % 2) * iter
				// 		* 40, 0, 200);
				color = create_trgb(bright,bright,bright,255);
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
	fractal.y = 1.5;
	fractal._y = -1 * fractal.y;
	fractal.x = 0.75;
	fractal._x = -2.25;
	if (!(fractal.mlx = mlx_init(WIDTH, HEIGHT, "fract_ol", true)))
		return (EXIT_FAILURE);
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);

	// img->enabled = true;
	// memset(fractal.img->pixels, 255, fractal.img->width * fractal.img->height * sizeof(int));
	// mlx_image_to_window(mlx, img, 5, 0);
	// fractal(-1.75, -0.25, 0.25, 0.45);
	draw_fractal(&fractal);
	// mlx_loop_hook(fractal.mlx, &hook(), fractal.mlx);
	mlx_loop_hook(fractal.mlx, &hook, &fractal);
	mlx_loop(fractal.mlx);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
