/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:58:28 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/04 05:02:23 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t get_color(int iterations, int max_iter, int color_shift)
{
	double t;

	if (iterations >= max_iter)
		return (BLACK);
	// Algoritmo de colorização simples mas eficaz
	t = (double)iterations / max_iter;
	// Aplica shift de cor (para bônus futuro)
	t = fmod(t + (color_shift * 0.01), 1.0);
	// Calcula componentes RGB
	int r = (int)(255 * (1 - t) * t * t * t * 9);
	int g = (int)(255 * (1 - t) * (1 - t) * t * t * 15);
	int b = (int)(255 * (1 - t) * (1 - t) * (1 - t) * t * 8.5);
	// Garante que valores estão no range [0, 255]
	r = (r > 255) ? 255 : (r < 0) ? 0 : r;
	g = (g > 255) ? 255 : (g < 0) ? 0 : g;
	b = (b > 255) ? 255 : (b < 0) ? 0 : b;
	// Retorna cor no formato RGBA
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}
