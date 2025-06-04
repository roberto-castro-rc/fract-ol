#ifndef FRACTOL_H
# define FRACTOL_H


#include "libs/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_INTER 50

// Configurações dos fractais
# define MAX_ITERATIONS 100
# define ESCAPE_RADIUS 2.0

// Tipos de fractal
# define MANDELBROT 1
# define JULIA 2




// Estrutura para números complexos
typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;


// Estrutura principal do programa
typedef struct s_fractol
{
	// MLX relacionados
	mlx_t		*mlx;
	mlx_image_t	*img;

	// Configurações da janela
	int			width;
	int			height;

	// Tipo de fractal atual
	int			fractal_type;

	// Parâmetros de visualização
	double		zoom;
	double		offset_x;
	double		offset_y;
	int			max_iter;

	// Parâmetros específicos do Julia
	t_complex	julia_c;

	// Sistema de cores
	int			color_shift;
}	t_fractol;


int	window(void);
// === MATEMÁTICA DOS FRACTAIS ===
int			mandelbrot(double c_real, double c_imag, int max_iter);
int			julia(double z_real, double z_imag, double c_real, double c_imag, int max_iter);

// === RENDERIZAÇÃO ===
void		render_fractal(t_fractol *data);
void		render_mandelbrot(t_fractol *data);
void		render_julia(t_fractol *data);


t_complex pixel_to_complex(int x, int y, t_fractol *data);
int	veriction_args(int argc, char **argv);

#endif
