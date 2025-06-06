/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:38:27 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 02:46:17 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(double c_real, double c_imag, int max_iter)
{
	double	z_real;
	double	z_imag;
	double	z_real_sq;
	double	z_imag_sq;
	int		iter;

	z_real = 0.0;
	z_imag = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		z_real_sq = z_real * z_real;
		z_imag_sq = z_imag * z_imag;
		if (z_real_sq + z_imag_sq > 4.0)
			break ;
		z_imag = 2.0 * z_real * z_imag + c_imag;
		z_real = z_real_sq - z_imag_sq + c_real;
		iter++;
	}
	return (iter);
}

int	julia(double z_real, double z_imag, t_fractol *fractal)
{
	double	z_real_sq;
	double	z_imag_sq;
	int		iter;

	iter = 0;
	while (iter < fractal->max_iter)
	{
		z_real_sq = z_real * z_real;
		z_imag_sq = z_imag * z_imag;
		if (z_real_sq + z_imag_sq > 4.0)
			break ;
		z_imag = 2.0 * z_real * z_imag + fractal->julia_c.imag;
		z_real = z_real_sq - z_imag_sq + fractal->julia_c.real;
		iter++;
	}
	return (iter);
}

t_complex	pixel_to_complex(int x, int y, t_fractol *data)
{
	t_complex	c;

	c.real = (x - data->width / 2.0)
		* (4.0 / data->width) / data->zoom + data->offset_x;
	c.imag = (y - data->height / 2.0)
		* (4.0 / data->height) / data->zoom + data->offset_y;
	return (c);
}
