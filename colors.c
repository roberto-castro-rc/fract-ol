/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:58:28 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/04 19:48:41 by rpaulo-c         ###   ########.fr       */
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


// 🆕 NOVO: Função para calcular componente R (vermelho)
static int	calculate_red(double t)
{
	int	r;

	r = (int)(255 * (1 - t) * t * t * t * 9);
	return (clamp_color(r));
}

// 🆕 NOVO: Função para calcular componente G (verde)
static int	calculate_green(double t)
{
	int	g;

	g = (int)(255 * (1 - t) * (1 - t) * t * t * 15);
	return (clamp_color(g));
}

// 🆕 NOVO: Função para calcular componente B (azul)
static int	calculate_blue(double t)
{
	int	b;

	b = (int)(255 * (1 - t) * (1 - t) * (1 - t) * t * 8.5);
	return (clamp_color(b));
}

// 🔧 REFATORADO: Função principal conforme norminette
uint32_t	get_color(int iterations, int max_iter, int color_shift)
{
	double		t;
	int			r;
	int			g;
	int			b;

	if (iterations >= max_iter)
	return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.01), 1.0);
	r = calculate_red(t);
	g = calculate_green(t);
	b = calculate_blue(t);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

uint32_t	get_color_advanced(int iterations, int max_iter, t_fractol *fractal)
{
	if (fractal->color_scheme == 1)
		return (get_color_psychedelic(iterations, max_iter, fractal->color_shift));
	else if (fractal->color_scheme == 2)
		return (get_color_fire(iterations, max_iter, fractal->color_shift));
	else if (fractal->color_scheme == 3)
		return (get_color_ocean(iterations, max_iter, fractal->color_shift));
	else
		return (get_color(iterations, max_iter, fractal->color_shift));
}
/* ************************************************************************** */
/*                    ESQUEMAS DE CORES ALTERNATIVOS                         */
/* ************************************************************************** */

// 🎨 BÔNUS: Diferentes algoritmos de colorização
uint32_t	get_color_psychedelic(int iterations, int max_iter, int color_shift)
{
	double		t;
	int			r;
	int			g;
	int			b;

	if (iterations >= max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.02), 1.0);
	// Algoritmo psicodélico - cores mais vibrantes
	r = (int)(255 * sin(t * 16 + color_shift * 0.1));
	g = (int)(255 * sin(t * 13 + color_shift * 0.1 + 2));
	b = (int)(255 * sin(t * 17 + color_shift * 0.1 + 4));
	r = clamp_color(abs(r));
	g = clamp_color(abs(g));
	b = clamp_color(abs(b));
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

uint32_t	get_color_fire(int iterations, int max_iter, int color_shift)
{
	double		t;
	int			r;
	int			g;
	int			b;

	if (iterations >= max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.01), 1.0);
	// Algoritmo de fogo - tons quentes
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
	return ((clamp_color(r) << 24) | (clamp_color(g) << 16) |
			(clamp_color(b) << 8) | 0xFF);
}

uint32_t	get_color_ocean(int iterations, int max_iter, int color_shift)
{
	double		t;
	int			r;
	int			g;
	int			b;

	if (iterations >= max_iter)
		return (BLACK);
	t = (double)iterations / max_iter;
	t = fmod(t + (color_shift * 0.01), 1.0);
	// Algoritmo oceano - tons azuis/verdes
	r = (int)(255 * t * 0.3);
	g = (int)(255 * (1 - t) * t * 4);
	b = (int)(255 * (1 - t * 0.5));
	return ((clamp_color(r) << 24) | (clamp_color(g) << 16) |
			(clamp_color(b) << 8) | 0xFF);
}
