#include "fractol.h"

int main (int argc, char **argv)
{
	int fractal;
	fractal = veriction_args(argc, argv);
	printf("%d", fractal);
	if(fractal == 1)
	{
		mandelbrot();
	}
	else if(fractal == 2)
	{
		julia();
	}
	return (0);
}

int	veriction_args(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Error: No arguments given\n can be: mandelbrot, julia, burningship\n");
		return (0);
	}
	else if (argc > 4)
	{
		printf("Error: Too many arguments\n can be: mandelbrot, julia, burningship\n");
		return (0);
	}
	else if(strcmp(argv[1], "mandelbrot") == 0)
	{
		if (argc != 2)
			return (0);
		return (1);
	}
	else if(strcmp(argv[1], "julia") == 0)
	{
		if (argc != 4)
			return (0);
		return (2);
	}
	printf("Error: Invalid argument\n");
	return (0);
}
//
