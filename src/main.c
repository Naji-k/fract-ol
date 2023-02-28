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

void render_fractal_set(const char set, t_fractal* fractal)
{
	static const t_fractal_set_list fractal_set[256] = {
		['M'] = draw_fractal_mandelbrot,
		['J'] = draw_julia_set,
	};
	if (fractal_set[(int)set])
		fractal_set[(int)set](fractal);
}

int shuffle_color(int value)
{
	if (value <= 200)
		value += 30;
	else if (value > 200)
		value -= 20;
	return (value);
}

void move_left(t_fractal* fractal)
{
	float t = 0;
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.001;
		// fractal->img->instances[0].x -= 5;
		// el.style.left = Math.floor((window.innerWidth / 2) - (el.offsetWidth / 2)) + 'px';
		// t = floor((WIDTH / 2) - (fractal->width) / 2);
		fractal->offset = remap(t,0,WIDTH,fractal->_x,fractal->x);
		printf("\n\n%f\n\n",fractal->offset);
	fractal->x += 0.1;
	fractal->_x += 0.1;

	// draw_fractal_mandelbrot(fractal);
}

void move_up(t_fractal* fractal)
{
	if (fractal->zoom_level >= 50)
		fractal->offset = 0.005;
	else if (fractal->zoom_level >= 150)
		fractal->offset = 0.001;
	fractal->y += 0.1;
	fractal->_y += 0.1;
	// fractal->height = fractal->height * 0.95;
	// re_factor(fractal);
	// draw_fractal_mandelbrot(fractal);
}

void	hook(void *param)
{
	t_fractal* fractal;
	float X,Y;
	fractal = param;

	if (mlx_is_key_down(fractal->mlx, MLX_KEY_J))
	{
		// mlx_delete_image(fractal->mlx,fractal->img);

		// fractal->img2 = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);

		// mlx_image_to_window(fractal->mlx,fractal->img2,0,0);


		fractal->set = 'J';
		mlx_get_mouse_pos(fractal->mlx,&fractal->pos_x,&fractal->pos_y);
		X = remap(fractal->pos_x,0,WIDTH,fractal->_x,fractal->x) ;
		Y = remap(fractal->pos_y,0,HEIGHT,fractal->y,fractal->_y);
		fractal->cx = X;
		fractal->cy = Y;
		run_fractal(fractal);
		// draw_julia_set(fractal);
	}
}

void my_key_func(mlx_key_data_t keydata, void* param)
{
	t_fractal	*fractal;

	fractal = param;
	
	if (keydata.key == MLX_KEY_ESCAPE  && keydata.action == MLX_PRESS)
		mlx_close_window(fractal->mlx);

 	if (keydata.key == MLX_KEY_Z  && keydata.action == MLX_PRESS)
	{
		// double center_x = (fractal->x + fractal->_x) / 2;
		// fractal->x  -= center_x + fractal->x * 0.95;
		// fractal->_x  -= center_x +  fractal->_x * 0.95;
		// fractal->y  = fractal->y * 0.95;
		// fractal->_y  = fractal->_y * 0.95;

		fractal->x  = fractal->x  * 0.95;
		fractal->_x  = fractal->_x * 0.95;
		fractal->y  = fractal->y * 0.95;
		fractal->_y  = fractal->_y * 0.95;


		// double w_temp = fractal->width;
		// double h_temp = fractal->height;

		fractal->max_iter += 1;
		// fractal->height = fractal->height * 1.05;
		// fractal->width = fractal->width * 1.05;
		
		// double scale = 0.05;
		// double offsetX = fractal->x ;
		// double offsetY = fractal->y;
		// double offset_X = fractal->_x ;
		// double offset_Y = fractal->_y;
		// printf("offsetX=%f\n,offsetY=%f\n", offsetX,offsetY);

		// fractal->x -= fractal->x - fractal->offset_x ;
		// fractal->_x -= fractal->_x -  fractal->offset_x ;
		// fractal->y -= fractal->y - fractal->offset_y ;
		// fractal->_y -= fractal->_y -  fractal->offset_y;
		// fractal->zoom /= 1.05;
		fractal->zoom_level +=1;
		// move_left(fractal);
		// move_up (fractal);
		// re_factor(fractal);

// printf("\nscale=%Lf\n",fractal->x);
		// draw_fractal_mandelbrot(fractal);
		run_fractal(fractal);

		printf("f->x=%Lf\n_x=%Lf\ny=%Lf\n_y=%Lf\nZ_level=%f\n", fractal->x, fractal->_x,
			fractal->y, fractal->_y, fractal->zoom_level);
		// printf("width=%f\nhight=%f\n",fractal->width, fractal->height);
	}
	if (keydata.key == MLX_KEY_X  && keydata.action == MLX_PRESS)
	{ //zoom_out
		fractal->max_iter -= 1;
		// fractal->height = fractal->height * 0.95;
		// fractal->width = fractal->width * 0.95;
		// fractal->zoom *= 1.05;
		// re_factor(fractal);
		fractal->x  = fractal->x  * 1.05;
		fractal->_x  = fractal->_x * 1.05;
		fractal->y  = fractal->y * 1.05;
		fractal->_y  = fractal->_y * 1.05;

		fractal->zoom_level -=1;
		// draw_fractal_mandelbrot(fractal);
		run_fractal(fractal);

	}
	if (keydata.key == MLX_KEY_DOWN  && keydata.action == MLX_PRESS)
	{ //go_down
		// =====================================================================
		// fractal->y += get_percentage(tmp, 10);
		// fractal->_y += get_percentage(tmp, 10);
		if (fractal->zoom_level >= 50)
			fractal->offset = 0.005;
		else if (fractal->zoom_level >= 150)
			fractal->offset = 0.001;
		fractal->y -= fractal->offset;
		fractal->_y -= fractal->offset;

		// fractal->_y = 0.25;
		// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
		// 		fractal->y, fractal->_y);
		// draw_fractal_mandelbrot(fractal);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_UP  && keydata.action == MLX_PRESS)
	{ //go_up
		if (fractal->zoom_level >= 50)
			fractal->offset = 0.005;
		else if (fractal->zoom_level >= 150)
			fractal->offset = 0.0001;
		fractal->y += fractal->offset ;
		fractal->_y += fractal->offset;
		// fractal->height = fractal->height * 0.95;
		// re_factor(fractal);
		// draw_fractal_mandelbrot(fractal);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_LEFT  && keydata.action == MLX_PRESS)
	{ //go_left
		if (fractal->zoom_level >= 50)
			fractal->offset = 0.005;
		else if (fractal->zoom_level >= 150)
			fractal->offset = 0.001;
		// fractal->img->instances[0].x -= 5;
		fractal->x += fractal->offset;
		fractal->_x += fractal->offset;

		// draw_fractal_mandelbrot(fractal);
		run_fractal(fractal);
		// printf("f->x=%f\n_x=%f\ny=%f\n_y=%f\n", fractal->x, fractal->_x,
		// 		fractal->y, fractal->_y);
	}
	if (keydata.key == MLX_KEY_RIGHT  && keydata.action == MLX_PRESS)
	{ //go_right
		if (fractal->zoom_level >= 50)
			fractal->offset = 0.005;
		else if (fractal->zoom_level >= 150)
			fractal->offset = 0.001;
		fractal->x -= fractal->offset ;
		fractal->_x -= fractal->offset ;
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_C  && keydata.action == MLX_PRESS)
	{//c change color
		fractal->color = shuffle_color(fractal->color);
		run_fractal(fractal);
	}
	if (keydata.key == MLX_KEY_D  && keydata.action == MLX_PRESS)
	{//D print debugging

	printf("f->x=%Lf\n_x=%Lf\ny=%Lf\n_y=%Lf\nmax_iter=%d\nfra.w=%f\n,fra.h=%f\nre_fac=%f\nim_fac=%f\n", fractal->x,
			fractal->_x, fractal->y, fractal->_y, fractal->max_iter,fractal->width,fractal->height, fractal->re_factor, fractal->im_factor);
	}
	if (keydata.key ==MLX_KEY_P  && keydata.action == MLX_PRESS)
	{
		float X,Y;
		mlx_get_mouse_pos(fractal->mlx, &fractal->pos_x, &fractal->pos_y);
		X = remap(fractal->pos_x,0,WIDTH,fractal->_x,fractal->x) ;
		Y = remap(fractal->pos_y,0,HEIGHT,fractal->y,fractal->_y);
		fractal->cx = X;
		fractal->cy = Y;
		printf("screen.x=%d\nscreen.y=%d\nX_trans=%f\nY_trans=%f\n",fractal->pos_x,fractal->pos_y,X,Y);
	}

	if (keydata.key == MLX_KEY_0  && keydata.action == MLX_PRESS)
	{
		reset_defaults(fractal);

		re_factor(fractal);
		// draw_fractal_mandelbrot(fractal);
		run_fractal(fractal);


	}
	if (keydata.key == MLX_KEY_T  && keydata.action == MLX_PRESS)
	{
		//when press on this Butto,
		float X,Y,Z;
		X = remap(fractal->pos_x,0,WIDTH,fractal->_x,fractal->x) ;
		Y = remap(fractal->pos_y,0,HEIGHT,fractal->y,fractal->_y);
		fractal->offset_x = X;
		fractal->offset_y = Y;
		Z = remap(40,0,WIDTH,fractal->_x,fractal->x);
		fractal->_x += 0.2;
		fractal->x += 0.2;
		fractal->y += 0.2;
		fractal->_y += 0.2;
		printf("\nZ=%f\n",Z);
		// printf("screen.x=%d\nscreen.y=%d\nX_trans=%f\nY_trans=%f\n",fractal->pos_x,fractal->pos_y,X,Y);

		draw_fractal_mandelbrot(fractal);


	}
	if (keydata.key == MLX_KEY_M  && keydata.action == MLX_PRESS)
	{
		fractal->set = 'M';
		// mlx_delete_image(fractal->mlx,fractal->img2);

		// fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);

		// mlx_image_to_window(fractal->mlx,fractal->img,0,0);
		run_fractal(fractal);
		// draw_julia_set(fractal);
	}

} 


void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (ydelta > 0)
	{
		// mlx_get_mouse_pos(fractal->mlx, &fractal->pos_x, &fractal->pos_y);
		// printf("screen.x=%d\nscreen.y=%d",fractal->pos_x,fractal->pos_y);

		fractal->max_iter += 1;
		fractal->height = fractal->height * 1.05;
		fractal->width = fractal->width * 1.05;
		fractal->zoom_level += 1;
		run_fractal(fractal);
		// draw_fractal_mandelbrot(fractal);
	}
	else if (ydelta < 0)
	{
		
		fractal->max_iter -= 1;
		fractal->height = fractal->height * 0.95;
		fractal->width = fractal->width * 0.95;
		// fractal->pos_x = remap(fractal->pos_x,0,WIDTH,-2,1);
		// fractal->pos_y = remap(fractal->pos_y,0,WIDTH,-2,1);
		// fractal->x += get_percentage(fractal->x, 30) + fractal->pos_x;
		// fractal->_x += get_percentage(fractal->_x, 30) + fractal->pos_x;
		// fractal->y += get_percentage(fractal->y, 30) + fractal->pos_y ;
		// fractal->_y += get_percentage(fractal->_y, 30) + fractal->pos_y;
		fractal->zoom_level -= 1;
		run_fractal(fractal);
		// draw_fractal_mandelbrot(fractal);
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
	fractal->re_factor = (fractal->x - fractal->_x)  * fractal->zoom / (fractal->width - 1);
	fractal->im_factor = (fractal->y - fractal->_y)  * fractal->zoom / (fractal->height - 1) ;
	// printf("re_fac=%f\nim_fac=%f",fractal->re_factor, fractal->im_factor);

}

void	draw_fractal_mandelbrot(t_fractal *fractal)
{
	int		color;
	// float	bright;
	// int		o_bright;

	// float	hue;
	double zx, zy, tempx;
	double continues_iter, mag;
	int x, y;
	int maxx, maxy, iter;
	maxx = WIDTH;
	maxy = HEIGHT;
	x = 0;
	y = 0;
	fractal->r = -1 * (WIDTH - fractal->width);
	// mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
	while (x < maxx)
	{
		y = 0;
		while (y < maxy)
		{
			//c_real
			fractal->cx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			// fractal->cx = fractal->_x + x * fractal->re_factor ;
			// cx = fractal->width / 2 + fractal->_x;
			// fractal->cx = (x - fractal->width) / (fractal->zoom * fractal->width);
			//c_imag
			// fractal->cy = fractal->y - y * fractal->im_factor;
			fractal->cy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			// fractal->cy = (y - fractal->height) / (fractal->zoom * fractal->height);
			
			//z_real
			zx = 0;
			//z_imag
			zy = 0;
			iter = 1;
			// dist = distance(0, 0, zx, zy);
			while (((zx * zx) + (zy * zy)) < 4 && (++iter <= fractal->max_iter))
			{
				tempx = (zx * zx) - (zy * zy) + fractal->cx;
				zy = (2 * zx * zy) + fractal->cy;
				zx = tempx;
			}
			// bright = remap(iter, 0, fractal->max_iter, 0, 255);
			// o_bright = get_percentage(fractal->max_iter, 75);
			if (iter == (fractal->max_iter + 1))
				// || bright < log2(fractal->max_iter))
			// if (iter == (fractal->max_iter))
			{
				// 	// interior, part of set, black
				// bright = 0;
				// color = create_trgb(0, 0, 0, 0);
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
				// color = get_rgba(100, 50, 200, 255);
				color = get_rgba(continues_iter, iter * fractal->color, iter * fractal->color * 11, 255);
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

void reset_defaults(t_fractal *fractal)
{
	fractal->width = WIDTH;
	fractal->height = HEIGHT;
	// fractal->y = 1.5;
	fractal->_y = -2;
	fractal->_x = -2;
	fractal->x = 2;
	// fractal->y = fractal->_y + (fractal->x - fractal->_x) * (fractal->height / fractal->width);
	fractal->y = 2;
	fractal->r = 2;
	fractal->zoom = 1;
	// re_factor(fractal);

	fractal->max_iter = 64;
	fractal->zoom_level = 1;
	fractal->offset = 0.025;
	fractal->height = HEIGHT;
	fractal->width = WIDTH;
	fractal->color = 10;
}

void draw_julia_set(t_fractal *fractal)
{
	int		color;
	float	bright;

	double zx, zy, tempx;
	double continues_iter, mag;
	int x, y;
	int maxx, maxy, iter;
	maxx = WIDTH;
	maxy = HEIGHT;
	x = 0;
	y = 0;
	while (x < maxx)
	{
		y = 0;
		while (y < maxy)
		{
			//c_real
			zx = remap(x, 0, fractal->width, fractal->_x, fractal->x);
			// cx = fractal->_x + x * fractal->re_factor;
			// cx = fractal->width / 2 + fractal->_x;
			//c_imag
			// cy = fractal->y - y * fractal->im_factor;
			zy = remap(y, 0, fractal->height, fractal->_y, fractal->y);
			
			//z_real

			//z_imag

			iter = 1;
			// dist = distance(0, 0, zx, zy);
			while (((zx * zx) + (zy * zy)) < 4 * fractal->x && (++iter <= fractal->max_iter))
			{
				tempx = (zx * zx) - (zy * zy);
				zy = (2 * zx * zy) + fractal->cy;
				zx = tempx + fractal->cx;
			}
			bright = remap(iter, 0, fractal->max_iter, 0, 255);
			// o_bright = get_percentage(fractal->max_iter, 75);
			if (iter == (fractal->max_iter + 1))
				// || bright < log2(fractal->max_iter))
			// if (iter == (fractal->max_iter))
			{
				// 	// interior, part of set, black
				bright = 0;
				color = create_trgb(0, 0, 0, 0);
				mlx_put_pixel(fractal->img, x, y, 255);
			}
			// if (iter < (fractal->max_iter))
			else
			{
				mag = sqrt((zx * zx) + (zy * zy));
				continues_iter = iter + 1 - (log(2) / fabs(mag)) / log(2);
				// color = create_trgb(255, bright, bright, bright);
				color = get_rgba(continues_iter, iter * fractal->color, iter * fractal->color * 11, 255);
				mlx_put_pixel(fractal->img, x, y, color);

			}

			y++;
		}
		x++;
	}
}
void run_fractal(t_fractal* fractal)
{
	render_fractal_set(fractal->set,fractal);
}


int	main(int argc, char** argv)
{

	t_fractal	fractal;
	reset_defaults(&fractal);
	char *fractals[] = {"Mandelbrot" , "Julia"};
	if (argc <  2)
	{
		int i;
		i = 0;
		while (i < 2)
			printf("%s\n",fractals[i++]);
	}
	else if (argc == 2 && strcmp(argv[1], "Mandelbrot") == 0)
	{
		if (!(fractal.mlx = mlx_init(WIDTH + 100, HEIGHT, "fract_ol",true)))
			return (EXIT_FAILURE);

		fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);

		mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
		fractal.set = 'M';
		// mlx_set_setting(MLX_STRETCH_IMAGE, 1);
		// img->enabled = true;
		// memset(fractal.img->pixels, 255, fractal.img->width * fractal.img->height
		// * sizeof(int));
		// mlx_image_to_window(mlx, img, 5, 0);
		// fractal(-1.75, -0.25, 0.25, 0.45);
		fractal.mlx->delta_time = 0.05;
		draw_fractal_mandelbrot(&fractal);
		mlx_key_hook(fractal.mlx,my_key_func,&fractal);
		mlx_scroll_hook(fractal.mlx, &my_scrollhook ,&fractal);
		mlx_loop_hook(fractal.mlx, &hook, &fractal);
		// printf("END====\nf->x=%f\n_x=%f\ny=%f\n_y=%f\nmax_iter=%d", fractal.x,
		// 		fractal._x, fractal.y, fractal._y, fractal.max_iter);
		mlx_loop(fractal.mlx);
		mlx_terminate(fractal.mlx);
		return (EXIT_SUCCESS);
	}
	else if (argc == 2 && strcmp(argv[1], "Julia") == 0)
	{
		if (!(fractal.mlx = mlx_init(WIDTH, HEIGHT, "fract_ol", true)))
			return (EXIT_FAILURE);
		fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
		mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
		fractal.set = 'J';
		run_fractal(&fractal);

		mlx_scroll_hook(fractal.mlx, &my_scrollhook ,&fractal);
		mlx_loop_hook(fractal.mlx, &hook, &fractal);
		mlx_key_hook(fractal.mlx,my_key_func,&fractal);
		mlx_loop(fractal.mlx);
		mlx_terminate(fractal.mlx);
		return (EXIT_SUCCESS);
	}
/* 	else if (argc == 2 && strcmp(argv[1], "Both") == 0)
	{
		if (!(fractal.mlx = mlx_init(1610, HEIGHT, "fract_ol", true)))
			return (EXIT_FAILURE);
			fractal.img = mlx_new_image(fractal.mlx,WIDTH, HEIGHT);
			draw_fractal_mandelbrot(&fractal);
			mlx_image_to_window(fractal.mlx,fractal.img,0,0);
			
			fractal.img2 = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
			mlx_image_to_window(fractal.mlx,fractal.img2,810,0);
			draw_julia_set(&fractal);
			mlx_scroll_hook(fractal.mlx, &my_scrollhook ,&fractal);
			mlx_loop_hook(fractal.mlx, &hook, &fractal);
			mlx_key_hook(fractal.mlx,my_key_func,&fractal);
			mlx_loop(fractal.mlx);
			mlx_terminate(fractal.mlx);
			return (EXIT_SUCCESS);
	} */

}