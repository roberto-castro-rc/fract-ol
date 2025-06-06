/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 05:19:17 by rpaulo-c          #+#    #+#             */
/*   Updated: 2025/06/06 08:17:32 by rpaulo-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (EXIT_FAILURE);
	}
	render_fractal(&fractal);
	mlx_key_hook(fractal.mlx, key_hook, &fractal);
	mlx_scroll_hook(fractal.mlx, scroll_hook, &fractal);
	mlx_close_hook(fractal.mlx, close_hook, &fractal);
	mlx_mouse_hook(fractal.mlx, mouse_hook, &fractal);
	mlx_loop(fractal.mlx);
	cleanup_fractol(&fractal);
	return (0);
}

int	validate_args(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putendl_fd("Error: No arguments given", 1);
		ft_putendl_fd("can be: mandelbrot, julia", 1);
		return (0);
	}
	if (argc == 2 && !strcmp(argv[1], "mandelbrot"))
		return (1);
	if (argc == 4 && !strcmp(argv[1], "julia"))
	{
		return (1);
	}
	ft_putendl_fd("Error: Too many arguments\n can be: mandelbrot, julia", 1);
	return (0);
}

void	print_usage(void)
{
	ft_putendl_fd("Usage: ./fractol <fractal_type> [params]", 1);
	ft_putendl_fd("Fractal types:", 1);
	ft_putendl_fd("mandelbrot", 1);
	ft_putendl_fd("julia <c_real> <c_imag>", 1);
	ft_putendl_fd("Example: ./fractol julia -0.4 0.6", 1);
}

// void	error_exit(char *message, t_fractol *fractal)
// {
// 	if (message)
// 	{
// 		ft_putstr_fd("Error: ", 2);
// 		ft_putendl_fd(message, 2);
// 	}
// 	if (fractal)
// 	{
// 		cleanup_fractol(fractal);
// 	}
// }
