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

void	hook(void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fractal->mlx);
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_Z))
	{ //zoom_in
		// fractal->max_iter += get_percentage(fractal->max_iter, 30);
		int temp = +300;
		// temp *= 0.95;
		// fractal->x += temp / 2;
		// remap(temp,)
		
		fractal->x -= get_percentage(fractal->x, 30);
		fractal->_x -= get_percentage(fractal->_x, 30);

		// fractal->y -= get_percentage(fractal->y, 30);
		fractal->_y -= get_percentage(fractal->_y, 30);
			fractal->y = fractal->_y + (fractal->x - fractal->_x) * (HEIGHT / WIDTH);

		fractal->zoom_level +=1;
		draw_fractal_mandelbrot(fractal);
		printf("temp=%d\n",temp);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_X))
	{ //zoom_out
		// fractal->max_iter -= get_percentage(fractal->max_iter, 30);
		fractal->x += get_percentage(fractal->x, 30);
		fractal->_x += get_percentage(fractal->_x, 30);
		// fractal->y += get_percentage(fractal->y, 30);
		fractal->_y += get_percentage(fractal->_y, 30);

			fractal->y = fractal->_y + (fractal->x - fractal->_x) * (HEIGHT / WIDTH);

		fractal->zoom_level -=1;
		draw_fractal_mandelbrot(fractal);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN))
	{ //go_down
		// =====================================================================
		// fractal->y += get_percentage(tmp, 10);
		// fractal->_y += get_percentage(tmp, 10);
		fractal->y -= fractal->offset;
		fractal->_y -= fractal->offset;
		// fractal->_y = 0.25;
		// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
		// 		fractal->y, fractal->_y);
		draw_fractal_mandelbrot(fractal);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP))
	{ //go_up

		fractal->y += fractal->offset ;
		fractal->_y += fractal->offset;
		draw_fractal_mandelbrot(fractal);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT))
	{ //go_left
		// fractal->img->instances[0].x -= 5;
		fractal->x += fractal->offset;
		fractal->_x += fractal->offset;
		draw_fractal_mandelbrot(fractal);
		// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
		// 		fractal->y, fractal->_y);
	}
	if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT))
	{ //go_right
		fractal->x -= fractal->offset ;
		fractal->_x -= fractal->offset ;
		draw_fractal_mandelbrot(fractal);
	}
	// printf("f->x=%Lf\n_x=%Lf\ny=%Lf\n_y=%Lf\nmax_iter=%d\n", fractal->x,
	// 		fractal->_x, fractal->y, fractal->_y, fractal->max_iter);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (ydelta > 0)
	{
		mlx_get_mouse_pos(fractal->mlx, &fractal->pos_x, &fractal->pos_y);
		printf("screen.x=%d\nscreen.y=%d",fractal->pos_x,fractal->pos_y);
		fractal->pos_x = remap(fractal->pos_x,0,WIDTH,-2,1);
		fractal->pos_y = remap(fractal->pos_y,0,WIDTH,-2,1);

		fractal->x -= get_percentage(fractal->x, 30) - fractal->pos_x;
		fractal->_x -= get_percentage(fractal->_x, 30) - fractal->pos_x;
		fractal->y -= get_percentage(fractal->y, 30) - fractal->pos_y;
		fractal->_y -= get_percentage(fractal->_y, 30) - fractal->pos_y;
		fractal->zoom_level += 1;
		draw_fractal_mandelbrot(fractal);
	}
	else if (ydelta < 0)
	{
		
		// mlx_get_mouse_pos(fractal->mlx, &fractal->pos_x, &fractal->pos_y);
		printf("screen.x=%d\nscreen.y=%d",fractal->pos_x,fractal->pos_y);
		// fractal->pos_x = remap(fractal->pos_x,0,WIDTH,-2,1);
		// fractal->pos_y = remap(fractal->pos_y,0,WIDTH,-2,1);
		fractal->x += get_percentage(fractal->x, 30) + fractal->pos_x;
		fractal->_x += get_percentage(fractal->_x, 30) + fractal->pos_x;
		fractal->y += get_percentage(fractal->y, 30) + fractal->pos_y ;
		fractal->_y += get_percentage(fractal->_y, 30) + fractal->pos_y;
		fractal->zoom_level -= 1;
		draw_fractal_mandelbrot(fractal);
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

float	distance(int x1, int y1, int x2, int y2)
{
	int	res;

	res = sqrt((x2 - x1) * (x2 - x1) + ((y2 - y1) * (y2 - y1)));
	return (res);
}

void	draw_fractal_mandelbrot(t_fractal *fractal)
{
	int		color;
	float	bright;
	int		o_bright;

	// float	hue;
	double zx, zy, cx, cy, tempx, z, dist;
	double continues_iter, mag;
	int x, y;
	int maxx, maxy, iter;
	maxx = WIDTH;
	maxy = HEIGHT;
	x = 0;
	y = 0;
	// mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
	// for (x = 0; x < maxx; x++)
	while (x < maxx)
	{
		y = 0;
		// for (y = 0; y < maxy; y++)
		while (y < maxy)
		{
			//c_real
			// cx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			fractal->re_factor = (fractal->x - fractal->_x) / (WIDTH - 1);
			fractal->im_refactor = (fractal->y - fractal->_y) / (HEIGHT - 1);
			cx = fractal->_x + x * fractal->re_factor;
			// cx = fractal->width / 2 + fractal->_x;
			//c_imag
			// cy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			
			cy = fractal->y - y * fractal->im_refactor;
			//z_real
			zx = 0;
			//z_imag
			zy = 0;
			iter = 1;
			dist = distance(0, 0, zx, zy);
			while (((zx * zx) + (zy * zy)) < 4 && (++iter <= fractal->max_iter))
			{
				tempx = (zx * zx) - (zy * zy) + cx;
				zy = (2 * zx * zy) + cy;
				zx = tempx;
				z = (zx + zy);
			}
			bright = remap(iter, 0, fractal->max_iter, 0, 255);
			o_bright = get_percentage(fractal->max_iter, 75);
			if (iter == (fractal->max_iter + 1))
				// || bright < log2(fractal->max_iter))
			// if (iter == (fractal->max_iter))
			{
				// 	// interior, part of set, black
				// 	bright = 0;
				color = create_trgb(0, 0, 0, 0);
				mlx_put_pixel(fractal->img, x, y, 255);
			}
			// if (iter < (fractal->max_iter))
			else
			{
				mag = sqrt((zx * zx) + (zy * zy));
				// continues_iter = iter + 1 - log(log2(fabs(z)));
				continues_iter = iter + 1 - (log(2) / fabs(mag)) / log(2);
				// hue = 255 * continues_iter / fractal->max_iter;
				// hue = iter*255;
				// color = get_rgba((iter % 3) * iter , (iter % 2) * iter * 40,
				// 		100, 255);
				// color = create_trgb(255, bright, bright, bright);
				// color = get_rgba(bright, bright, bright, 255);
				color = get_rgba(iter * 5, iter * 10 , iter * 30, 255);
				mlx_put_pixel(fractal->img, x, y, color);
				// memset(img->pixels, 255, img->width * img->height
				// * sizeof(int));
			}
			// else
			// {
			// 	mlx_put_pixel(fractal->img, x, y, 255);
			// }
			y++;
		}
		x++;
	}
}


int32_t	main(void)
{
	t_fractal	fractal;

	// mlx_t	*mlx;
	// fractal.y = 2.000000000000;

	// fractal.y = 1.5;
	fractal._y = -2;
	fractal._x = -2.25;
	fractal.x = 1.75;
	fractal.y = fractal._y + (fractal.x - fractal._x) * (HEIGHT / WIDTH);
	// fractal.y = 2;

	fractal.re_factor = (fractal.x - fractal._x) / (WIDTH - 1);
	fractal.im_refactor = (fractal.y - fractal._y) / (HEIGHT - 1);

	fractal.max_iter = 150;
	fractal.zoom_level = 1;
	fractal.offset = 0.025;
	fractal.height = HEIGHT;
	fractal.width = WIDTH;
	if (!(fractal.mlx = mlx_init(WIDTH, HEIGHT, "fract_ol", true)))
		return (EXIT_FAILURE);
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
	// mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	// img->enabled = true;
	// memset(fractal.img->pixels, 255, fractal.img->width * fractal.img->height
	// * sizeof(int));
	// mlx_image_to_window(mlx, img, 5, 0);
	// fractal(-1.75, -0.25, 0.25, 0.45);
	draw_fractal_mandelbrot(&fractal);
	mlx_loop_hook(fractal.mlx, &hook, &fractal);
	mlx_scroll_hook(fractal.mlx, &my_scrollhook ,&fractal);

	// printf("END====\nf->x=%f\n_x=%f\ny=%f\n_y=%f\nmax_iter=%d", fractal.x,
	// 		fractal._x, fractal.y, fractal._y, fractal.max_iter);
	mlx_loop(fractal.mlx);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}
