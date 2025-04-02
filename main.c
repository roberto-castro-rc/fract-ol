// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libs/MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 12, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
int main(int argc, char **argv)
{
	int fractal;

	fractal = veriction_args(argc, argv);
	if(fractal == 0)
		return (0);
	else if(fractal == 1)
	{
		mandelbrot();
	}
	else if(fractal == 2)
	{
		julia();
	}
	else if(fractal == 3)
	{
		burningship();
	}
	return (0);
}
int main(int argc, char **argv)
{
	int fractal;
	mlx_t *mlx;

	fractal = veriction_args(argc, argv);
	mlx = mlx_init(WIDTH, HEIGHT, "Fractol", true);
	if (!mlx)
	{
		ft_printf("Error initializing MLX\n");
		return (0);
	}
	if(fractal == 0)
		return (0);
	else if(fractal == 1)
	{
		mandelbrot(mlx);
	}
	else if(fractal == 2)
	{
		julia(mlx);
	}
	else if(fractal == 3)
	{
		burningship(mlx);
	}

}
int	veriction_args(int argc, char **argv)
{
	if(argc < 2)
	{
		ft_printf("Error: No arguments given\n can be: mandelbrot, julia, burningship\n");
		return (0);
	}
	else if (argc > 4)
	{
		ft_printf("Error: Too many arguments\n can be: mandelbrot, julia, burningship\n");
		return (0);
	}
	else if(ft_strcmp(argv[1], "mandelbrot"))
	{
		return (1);
	}
	else if(ft_strcmp(argv[1], "julia"))
	{
		return (2);
	}
	else if(ft_strcmp(argv[1], "burningship"))
	{
		return (3);
	}
	else
	{
		ft_printf("Error: Invalid argument\n");
		return (0);
	}
}
