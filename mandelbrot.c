#include "fractol.h"

void	mandelbrot(void)
{
	printf("mandelbrot\n");
	window();
}
int calculate_mandelbrot(t_complex c, int max_iter)
{
    t_complex z;
    int iter;

    z.real = 0;
    z.imag = 0;
    iter = 0;

    while (iter < max_iter)
    {
        // Calcula z = z² + c
        double temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;

        // Verifica se diverge (|z| > 2)
        if (z.real * z.real + z.imag * z.imag > 4)
            break;
        iter++;
    }

    return (iter);
}
