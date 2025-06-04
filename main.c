#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fractal;

	if (!validate_args(argc, argv))
	{
		print_usage();
		return (1);
	}
	if (!init_fractol(&fractal, argv))
	{
		error_exit("Failed to initialize fractal", &fractal);
	}

	render_fractal(&fractal);

	mlx_key_hook(fractal.mlx, key_hook, &fractal);
	mlx_scroll_hook(fractal.mlx, scroll_hook, &fractal);
	mlx_close_hook(fractal.mlx, close_hook, &fractal);
	    mlx_mouse_hook(fractal.mlx, mouse_hook, &fractal);        // 🆕 NOVO: Hook para cliques do mouse
    mlx_cursor_hook(fractal.mlx, cursor_hook, &fractal);      // 🆕 NOVO: Hook para movimento do cursor

	mlx_loop(fractal.mlx);

	cleanup_fractol(&fractal);
	return (0);
}

int	validate_args(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Error: No arguments given\n can be: mandelbrot, julia\n");
		return (0);
	}
	if (argc == 2 && !strcmp(argv[1], "mandelbrot"))
		return (1);
	if (argc == 4 && !strcmp(argv[1], "julia"))
	{
		return (1);
	}
	printf("Error: Too many arguments\n can be: mandelbrot, julia, burningship\n");
	return (0);

}

void	print_usage(void)
{
	printf("Usage: ./fractol <fractal_type> [params]\n");
	printf("Fractal types:\n");
	printf("  mandelbrot\n");
	printf("  julia <c_real> <c_imag>\n");
	printf("Example: ./fractol julia -0.4 0.6\n");
}

void	error_exit(char *message, t_fractol *fractal)
{
	if (message)
	{
		fprintf(stderr, "Error: %s\n", message);
	}
	if (fractal)
	{
		cleanup_fractol(fractal);
	}
}
