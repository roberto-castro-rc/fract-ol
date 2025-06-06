#include "fractol.h"

int init_fractol(t_fractol *fractal, char **argv)
{
	// Inicialização da estrutura
	fractal->width = WIDTH;
	fractal->height = HEIGHT;
	fractal->zoom = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->max_iter = MAX_ITERATIONS;
	fractal->color_shift = 0;
	fractal->color_scheme = 0; // 0 = Esquema de cores padrão

	// 🆕 NOVO: Inicialização das variáveis do mouse
    fractal->mouse_pressed = 0;
    fractal->mouse_x = 0;
    fractal->mouse_y = 0;
    fractal->last_mouse_x = 0;
    fractal->last_mouse_y = 0;
	// Determina tipo de fractal
	fractal->fractal_type = parse_fractal_type(argv[1]);

	// Se for Julia, parse dos parâmetros
	if (fractal->fractal_type == JULIA)
	{
		if (!parse_julia_params(argv[2], argv[3], &fractal->julia_c))
			return (0);
	}

	fractal->mlx = mlx_init(fractal->width, fractal->height, "Fractol", true);
	if (!fractal->mlx)
		return (0);

	fractal->img = mlx_new_image(fractal->mlx, fractal->width, fractal->height);
	if (!fractal->img)
	{
		mlx_terminate(fractal->mlx);
		return (0);
	}
	if (mlx_image_to_window(fractal->mlx, fractal->img, 0, 0) < 0)
	{
		mlx_delete_image(fractal->mlx, fractal->img);
		mlx_terminate(fractal->mlx);
		return (0);
	}
	return (1);
}

int	parse_fractal_type(char *arg)
{
	if (!ft_strcmp(arg, "mandelbrot"))
		return (MANDELBROT);
	else if (!ft_strcmp(arg, "julia"))
		return (JULIA);
	return (0);
}

int	parse_julia_params(char *real_str, char *imag_str, t_complex *c)
{
	c->real = ft_atof(real_str);
	c->imag = ft_atof(imag_str);

	if (c->real < -2.0 || c->real > 2.0 || c->imag < -2.0 || c->imag > 2.0)
	{
		fprintf(stderr, "Invalid Julia parameters: %s, %s\n", real_str, imag_str);
	}
	return (1);
}

void	cleanup_fractol(t_fractol *fractal)
{
	if (fractal->img)
		mlx_delete_image(fractal->mlx, fractal->img);
	if (fractal->mlx)
		mlx_terminate(fractal->mlx);
}
