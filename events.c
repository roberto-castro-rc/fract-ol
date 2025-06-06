/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:03:43 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 08:00:25 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	handle_arrow_keys(int key, t_fractol *fractal)
{
	if (key == MLX_KEY_UP)
		fractal->offset_y -= 0.1 / fractal->zoom;
	else if (key == MLX_KEY_DOWN)
		fractal->offset_y += 0.1 / fractal->zoom;
	else if (key == MLX_KEY_LEFT)
		fractal->offset_x -= 0.1 / fractal->zoom;
	else if (key == MLX_KEY_RIGHT)
		fractal->offset_x += 0.1 / fractal->zoom;
	render_fractal(fractal);
}

static void	adjust_julia_parameter(t_fractol *fractal, double delta)
{
	if (fractal->fractal_type == JULIA)
	{
		fractal->julia_c.real += delta;
		if (fractal->julia_c.real > 2.0)
			fractal->julia_c.real = 2.0;
		else if (fractal->julia_c.real < -2.0)
			fractal->julia_c.real = -2.0;
	}
}

static void	handle_color_keys(mlx_key_data_t keydata, t_fractol *fractal)
{
	if (keydata.key == MLX_KEY_C)
	{
		fractal->color_shift = (fractal->color_shift + 10) % 100;
		render_fractal(fractal);
	}
	else if (keydata.key == MLX_KEY_V)
	{
		fractal->color_scheme = (fractal->color_scheme + 1) % 4;
		render_fractal(fractal);
		ft_putstr_fd("Color scheme changed: ", 1);
		ft_putchar_fd(fractal->color_scheme + '0', 1);
		ft_putendl_fd(" (0=default, 1=psychedelic, 2=fire, 3=ocean)", 1);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fractal->mlx);
	else if (keydata.key == MLX_KEY_C || keydata.key == MLX_KEY_V)
		handle_color_keys(keydata, fractal);
	else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		handle_arrow_keys(keydata.key, fractal);
	if (keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_EQUAL)
	{
		adjust_julia_parameter(fractal, 0.01);
		render_fractal(fractal);
	}
	else if (keydata.key == MLX_KEY_KP_SUBTRACT || keydata.key == MLX_KEY_MINUS)
	{
		adjust_julia_parameter(fractal, -0.01);
		render_fractal(fractal);
	}
}

void	close_hook(void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	mlx_close_window(fractal->mlx);
	exit(0);
}
