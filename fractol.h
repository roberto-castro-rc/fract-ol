#ifndef FRACTOL_H
# define FRACTOL_H


#include "libs/MLX42/include/MLX42/MLX42.h"
#include "libs/libft/libft.h"
#include <stdio.h>
# include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>




// Dimensões da janela
# define WIDTH 1200
# define HEIGHT 800

// Configurações dos fractais
# define MAX_ITERATIONS 250
# define ESCAPE_RADIUS 2.0

// Tipos de fractal
# define MANDELBROT 1
# define JULIA 2

// Cores básicas
# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define BLUE 0x0000FFFF
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define YELLOW 0xFFFF00FF
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

	// Parâmetros de visualização
	double		zoom;
	double		offset_x;
	double		offset_y;

	// Parâmetros do fractal
	int			max_iter;
	int			fractal_type;
	// Sistema de cores
	int			color_shift;
	int			color_scheme;
	// Parâmetros específicos do Julia
	t_complex	julia_c;

	// Controle do mouse
    int mouse_pressed;      // Estado do botão esquerdo
    int mouse_x;           // Posição X atual do mouse
    int mouse_y;           // Posição Y atual do mouse
    int last_mouse_x;      // Última posição X registrada
    int last_mouse_y;      // Última posição Y registrada

}	t_fractol;

// === INICIALIZAÇÃO E LIMPEZA ===
int			init_fractol(t_fractol *data, char **argv);
void		cleanup_fractol(t_fractol *data);
int			validate_args(int argc, char **argv);

// === PARSING DE ARGUMENTOS ===
int			parse_fractal_type(char *arg);
int			parse_julia_params(char *real_str, char *imag_str, t_complex *c);
void		print_usage(void);
// === MATEMÁTICA DOS FRACTAIS ===
int			mandelbrot(double c_real, double c_imag, int max_iter);
int			julia(double z_real, double z_imag, double c_real, double c_imag, int max_iter);
// === RENDERIZAÇÃO ===
void		render_fractal(t_fractol *data);
void		render_mandelbrot(t_fractol *data);
void		render_julia(t_fractol *data);
void 	put_pixel_to_image(mlx_image_t *img, int x, int y, uint32_t color);

// === CONVERSÕES E UTILIDADES ===
t_complex	pixel_to_complex(int x, int y, t_fractol *data);
uint32_t	get_color(int iterations, int max_iter, int color_shift);
uint32_t	get_color_psychedelic(int iterations, int max_iter, int color_shift);
uint32_t	get_color_fire(int iterations, int max_iter, int color_shift);
uint32_t	get_color_ocean(int iterations, int max_iter, int color_shift);
uint32_t	get_color_advanced(int iterations, int max_iter, t_fractol *fractal);
// === EVENTOS ===
void		key_hook(mlx_key_data_t keydata, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);
void		close_hook(void *param);
void		mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
void		cursor_hook(double xpos, double ypos, void *param);

void		error_exit(char *message, t_fractol *data);

#endif
