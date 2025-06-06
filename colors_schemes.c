/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_schemes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 06:32:29 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 06:32:30 by rpaulo-c         ###   ########.fr       */
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

uint32_t	get_color_psychedelic(int iterations, int max_iter, int color_shift)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations >= max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.02), 1.0);
	r = (int)(255 * sin(t * 16 + color_shift * 0.1));
	g = (int)(255 * sin(t * 13 + color_shift * 0.1 + 2));
	b = (int)(255 * sin(t * 17 + color_shift * 0.1 + 4));
	return ((clamp_color(abs(r)) << 24) | (clamp_color(abs(g)) << 16)
		| (clamp_color(abs(b)) << 8) | 0xFF);
}

uint32_t	get_color_fire(int iterations, int max_iter, int color_shift)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations >= max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.01), 1.0);
	if (t < 0.5)
	{
		r = (int)(255 * t * 2);
		g = (int)(255 * t * t * 4);
		b = 0;
	}
	else
	{
		r = 255;
		g = (int)(255 * (0.5 + t * 0.5));
		b = (int)(255 * (t - 0.5) * 2);
	}
	return ((clamp_color(r) << 24) | (clamp_color(g) << 16)
		| (clamp_color(b) << 8) | 0xFF);
}

uint32_t	get_color_ocean(int iterations, int max_iter, int color_shift)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations >= max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.01), 1.0);
	r = (int)(255 * t * 0.3);
	g = (int)(255 * (1 - t) * t * 4);
	b = (int)(255 * (1 - t * 0.5));
	return ((clamp_color(r) << 24) | (clamp_color(g) << 16)
		| (clamp_color(b) << 8) | 0xFF);
}
