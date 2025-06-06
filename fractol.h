/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:24:02 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 08:28:53 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libs/MLX42/include/MLX42/MLX42.h"
# include "libs/libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 600

# define MAX_ITERATIONS 150
# define ESCAPE_RADIUS 2.0

# define MANDELBROT 1
# define JULIA 2

# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define BLUE 0x0000FFFF
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define YELLOW 0xFFFF00FF

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
	double		zoom;
	double		offset_x;
	double		offset_y;
	int			max_iter;
	int			fractal_type;
	int			color_shift;
	int			color_scheme;
	t_complex	julia_c;
	int			mouse_pressed;
	int			mouse_x;
	int			mouse_y;
	int			last_mouse_x;
	int			last_mouse_y;
}	t_fractol;

int			init_fractol(t_fractol *data, char **argv);
void		cleanup_fractol(t_fractol *data);
int			validate_args(int argc, char **argv);
int			init_mlx(t_fractol *fractal);

// === ARGUMENT PARSING ===
int			parse_fractal_type(char *arg);
int			parse_julia_params(char *real_str, char *imag_str, t_complex *c);
void		print_usage(void);
// === FRACTAL MATH ===
int			mandelbrot(double c_real, double c_imag, int max_iter);
int			julia(double z_real, double z_imag, t_fractol *fractal);
// === RENDERING ===
void		render_fractal(t_fractol *data);
void		render_mandelbrot(t_fractol *data);
void		render_julia(t_fractol *data);
void		put_pixel_to_image(mlx_image_t *img, int x, int y, uint32_t color);
// === CONVERSIONS AND UTILITIES ===
t_complex	pixel_to_complex(int x, int y, t_fractol *data);
uint32_t	get_color(int iterations, int max_iter, int color_shift);
uint32_t	get_color_psychedelic(int iterations,
				int max_iter, int color_shift);
uint32_t	get_color_fire(int iterations, int max_iter, int color_shift);
uint32_t	get_color_ocean(int iterations, int max_iter, int color_shift);
uint32_t	get_color_advanced(int iterations,
				int max_iter, t_fractol *fractal);
// === EVENTS ===
void		key_hook(mlx_key_data_t keydata, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);
void		close_hook(void *param);
void		mouse_hook(mouse_key_t button,
				action_t action, modifier_key_t mods, void *param);
void		cursor_hook(double xpos, double ypos, void *param);
// void		error_exit(char *message, t_fractol *data);
#endif
