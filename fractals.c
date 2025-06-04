#include "fractol.h"

void	mandelbrot(void)
{
	printf("mandelbrot\n");
	window();
}
int	mandelbrot(double c_re, double c_im, int max_iter)
{
	double	z_re = 0;      // Parte real de z (número complexo que vai sendo calculado)
	double	z_im = 0;      // Parte imaginária de z
	int		iter = 0;      // Contador de iterações

	// Loop principal: continua até atingir max_iter OU z divergir (|z| > 2)
	// Por que 4? Porque |z|² = z_re² + z_im² > 4 significa |z| > 2
	while (iter < max_iter && (z_re * z_re + z_im * z_im) < 4)
	{
		// Fórmula do Mandelbrot: z = z² + c
		// (a + bi)² = a² - b² + 2abi
		// Então: z_novo = z_antigo² + c
		double temp = z_re * z_re - z_im * z_im + c_re;  // Nova parte real
		z_im = 2 * z_re * z_im + c_im;                   // Nova parte imaginária
		z_re = temp;                                     // Atribui nova parte real
		iter++;
	}
	// RETORNA: número de iterações antes da divergência
	// Se iter == max_iter: ponto pertence ao conjunto (cor escura/preta)
	// Se iter < max_iter: ponto divergiu (cor baseada na velocidade de divergência)
	return (iter);
}

/*
ARGUMENTOS QUE A FUNÇÃO RECEBE quando chamada de render_fractal():
- c_re: coordenada X do pixel convertida para o plano complexo (parte real de c)
- c_im: coordenada Y do pixel convertida para o plano complexo (parte imaginária de c)
- max_iter: número máximo de iterações (ex: 50, 100) - controla detalhes do fractal

PARA ONDE VAI O INTEIRO DEVOLVIDO:
- Vai para a variável 'iter' em render_fractal()
- É usado em get_color(iter, max_iter) para determinar a cor do pixel
- Quanto maior iter, mais "próximo" o ponto está do conjunto
*/
#include "fractol.h"

void	julia(void)
{
	printf("julia");
	window();
}
// FUNÇÃO JULIA - EXPLICAÇÃO DETALHADA
// A GRANDE DIFERENÇA: no Mandelbrot z começa em 0 e c é o ponto testado
// No Julia: z começa no ponto testado e c é uma CONSTANTE fixa!
int julia(double z_re, double z_im, double c_re, double c_im, int max_iter)
{
    // z_re e z_im JÁ VÊM como o ponto que estamos testando (coordenada do pixel)
    // NÃO começamos z em 0 como no Mandelbrot!

    // c_re e c_im são CONSTANTES fixas que definem qual Julia estamos calculando
    // Exemplos de constantes famosas:
    // c = -0.4 + 0.6i (Julia clássico)
    // c = -0.8 + 0.156i (formato de raio)
    // c = -0.7269 + 0.1889i (espiral)

    int iter = 0; // Contador de iterações

    // Loop principal: continua até atingir max_iter OU z divergir (|z| > 2)
    // Por que 4? Porque |z|² = z_re² + z_im² > 4 significa |z| > 2
    while (iter < max_iter && (z_re * z_re + z_im * z_im) < 4)
    {
        // Fórmula do Julia: z = z² + c (MESMA fórmula do Mandelbrot!)
        // (a + bi)² = a² - b² + 2abi
        // Então: z_novo = z_antigo² + c

        double temp = z_re * z_re - z_im * z_im + c_re; // Nova parte real
        z_im = 2 * z_re * z_im + c_im; // Nova parte imaginária
        z_re = temp; // Atribui nova parte real

        iter++;
    }

    // RETORNA: número de iterações antes da divergência
    // Se iter == max_iter: ponto pertence ao conjunto Julia (cor escura/preta)
    // Se iter < max_iter: ponto divergiu (cor baseada na velocidade de divergência)
    return (iter);
}

t_complex pixel_to_complex(int x, int y, t_fractol *data)
{
    t_complex c;

    // Mapeia pixel para plano complexo [-2, 2] com zoom e offset
    c.real = (x - data->width / 2.0) * (4.0 / data->width) / data->zoom + data->offset_x;
    c.imag = (y - data->height / 2.0) * (4.0 / data->height) / data->zoom + data->offset_y;

    return (c);
}
