/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:58:28 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 06:32:04 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	clamp_color(int color)
{
	if (color > 255)
		return (255);
	if (color < 0)
		return (0);
	return (color);
}

static uint32_t	calculate_default_color(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255 * (1 - t) * t * t * t * 9);
	g = (int)(255 * (1 - t) * (1 - t) * t * t * 15);
	b = (int)(255 * (1 - t) * (1 - t) * (1 - t) * t * 8.5);
	return ((clamp_color(r) << 24) | (clamp_color(g) << 16)
		| (clamp_color(b) << 8) | 0xFF);
}

uint32_t	get_color(int iterations, int max_iter, int color_shift)
{
	double	t;

	if (iterations >= max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.01), 1.0);
	return (calculate_default_color(t));
}

uint32_t	get_color_advanced(int iterations, int max_iter, t_fractol *fractal)
{
	if (fractal->color_scheme == 1)
		return (get_color_psychedelic(iterations, max_iter,
				fractal->color_shift));
	else if (fractal->color_scheme == 2)
		return (get_color_fire(iterations, max_iter, fractal->color_shift));
	else if (fractal->color_scheme == 3)
		return (get_color_ocean(iterations, max_iter, fractal->color_shift));
	else
		return (get_color(iterations, max_iter, fractal->color_shift));
}
