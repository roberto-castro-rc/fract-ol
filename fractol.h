#ifndef FRACTOL_H
# define FRACTOL_H


#include "libs/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_INTER 50


typedef struct s_complex
{
    double real;
    double imag;
} t_complex;




int	window(void);
void	julia(void);
void	mandelbrot(void);
int	veriction_args(int argc, char **argv);

#endif
