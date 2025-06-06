/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:00:09 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 06:11:39 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	apply_zoom(t_fractol *fractal, double ydelta)
{
	if (ydelta > 0)
		fractal->zoom *= 1.1;
	else
		fractal->zoom *= 0.9;
}

void	mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			fractal->mouse_pressed = 1;
			mlx_get_mouse_pos(fractal->mlx, &fractal->last_mouse_x,
				&fractal->last_mouse_y);
		}
		else if (action == MLX_RELEASE)
		{
			fractal->mouse_pressed = 0;
		}
	}
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_fractol	*fractal;
	int			delta_x;
	int			delta_y;
	double		move_factor;

	fractal = (t_fractol *)param;
	fractal->mouse_x = (int)xpos;
	fractal->mouse_y = (int)ypos;
	if (fractal->mouse_pressed)
	{
		delta_x = fractal->mouse_x - fractal->last_mouse_x;
		delta_y = fractal->mouse_y - fractal->last_mouse_y;
		move_factor = 2.0 / (fractal->width * fractal->zoom);
		fractal->offset_x -= delta_x * move_factor;
		fractal->offset_y -= delta_y * move_factor;
		fractal->last_mouse_x = fractal->mouse_x;
		fractal->last_mouse_y = fractal->mouse_y;
		render_fractal(fractal);
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractal;
	t_complex	mouse_before;
	t_complex	mouse_after;

	fractal = (t_fractol *)param;
	(void)xdelta;
	if (ydelta != 0)
	{
		mlx_get_mouse_pos(fractal->mlx, &fractal->mouse_x,
			&fractal->mouse_y);
		mouse_before = pixel_to_complex(fractal->mouse_x,
				fractal->mouse_y, fractal);
		apply_zoom(fractal, ydelta);
		mouse_after = pixel_to_complex(fractal->mouse_x,
				fractal->mouse_y, fractal);
		fractal->offset_x += mouse_before.real - mouse_after.real;
		fractal->offset_y += mouse_before.imag - mouse_after.imag;
		render_fractal(fractal);
	}
}
