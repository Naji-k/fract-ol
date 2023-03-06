/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 00:40:55 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/03/05 00:40:55 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static int	ft_atof_sign_space(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

double	ft_atof(const char *str)
{
	double	res;
	double	scale;
	int		sign;
	int		after_dot;
	int		i;

	res = 0;
	after_dot = 0;
	scale = 1;
	sign = 1;
	i = ft_atof_sign_space(str, &sign);
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
	{
		if (after_dot)
		{
			scale = scale / 10;
			res = res + (str[i] - '0') * scale;
		}
		else if (str[i] == '.')
			after_dot++;
		else
			res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
