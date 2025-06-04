#include "fractol.h"

void	render_fractal(t_fractol *fractal)
{
	if (fractal->fractal_type == MANDELBROT)
	{
		render_mandelbrot(fractal);
	}
	else if (fractal->fractal_type == JULIA)
	{
		render_julia(fractal);
	}
}

void	render_mandelbrot(t_fractol *fractal)
{
	uint32_t	color;
	t_complex	c;
	int			x;
	int			y;
	int			iter;
	y = 0;
	while (y < fractal->height)
	{
		x = 0;
		while (x < fractal->width)
		{
			c = pixel_to_complex(x, y, fractal);
			iter = mandelbrot(c.real, c.imag, fractal->max_iter);
			color = get_color(iter, fractal->max_iter, fractal->color_shift);
			put_pixel_to_image(fractal->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_julia(t_fractol *fractal)
{
	uint32_t	color;
	int			x;
	int			y;
	int			iter;
	t_complex	z;

	y = 0;
	while (y < fractal->height)
	{
		while (x < fractal->width)
		{
			z = pixel_to_complex(x, y, fractal);
			iter = julia(z.real, z.imag, fractal->julia_c.real, fractal->julia_c.imag, fractal->max_iter);
			color = get_color(iter, fractal->max_iter, fractal->color_shift);
			put_pixel_to_image(fractal->img, x, y, color);
			x++;
		}
		y++;
	}
}
