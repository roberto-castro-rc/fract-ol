/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:54:03 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 07:25:37 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_sign(char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (**str == '+')
		(*str)++;
	return (1);
}

static double	parse_integer_part(char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_decimal_part(char **str)
{
	double	fraction;
	int		decimal_places;

	fraction = 0.0;
	decimal_places = 0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			fraction = fraction * 10.0 + (**str - '0');
			decimal_places++;
			(*str)++;
		}
		while (decimal_places > 0)
		{
			fraction /= 10.0;
			decimal_places--;
		}
	}
	return (fraction);
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;

	if (!str)
		return (0.0);
	sign = parse_sign(&str);
	result = parse_integer_part(&str);
	fraction = parse_decimal_part(&str);
	return (sign * (result + fraction));
}
