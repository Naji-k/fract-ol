/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/07 18:05:01 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/07 18:05:01 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	check_input(int argc, char **argv, char **fractals_set, t_fractal *fractal)
{
	int	i;

	i = 0;
	if (argc < 2)
		print_available_fractals(fractals_set);
	else
	{
		while (strcmp(argv[1], fractals_set[i]) != 0)
		{
			i++;
			if (i > 2)
			{
				print_available_fractals(fractals_set);
				return (1);
			}
		}
		fractal->set = fractals_set[i][0];
		if (fractal->set == 'J' && argv[2] != NULL && argv[3] != NULL)
		{
			fractal->cx = ft_atof(argv[2]);
			fractal->cy = ft_atof(argv[3]);
		}
		return (0);
	}
	return (1);
}

void print_available_fractals (char **fractals)
{
	int i;
	i = 0;
	while(i < 3)
		printf("%s\n",fractals[i++]);
}