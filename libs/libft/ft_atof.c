/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:54:03 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/04 05:54:06 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		decimal_places;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	decimal_places = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			fraction = fraction * 10.0 + (*str - '0');
			decimal_places++;
			str++;
		}
	}
	while (decimal_places > 0)
	{
		fraction /= 10.0;
		decimal_places--;
	}
	return (sign * (result + fraction));
}
