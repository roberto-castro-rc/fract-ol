#include "fractol.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	if (keydata.action == MLX_RELEASE)
		return;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fractal->mlx);
	else if (keydata.key == MLX_KEY_UP)
	{
		fractal->offset_y -= 0.1 / fractal->zoom;
		render_fractal(fractal);
	}
	else if (keydata.key == MLX_KEY_DOWN)
	{
		fractal->offset_y += 0.1 / fractal->zoom;
		render_fractal(fractal);
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		fractal->offset_x -= 0.1 / fractal->zoom;
		render_fractal(fractal);
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		fractal->offset_x += 0.1 / fractal->zoom;
		render_fractal(fractal);
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractal;
	t_complex		mouse_complex;

	(void)xdelta;
	fractal = (t_fractol *)param;
	if (ydelta != 0)
	{
		// Converte posição do mouse para coordenadas complexas ANTES do zoom
		mouse_complex = pixel_to_complex(fractal->mouse_x, fractal->mouse_y, fractal);

		// Aplica zoom
		if (ydelta > 0) // Zoom in
			fractal->zoom *= 1.1;
		else if (ydelta < 0) // Zoom out
			fractal->zoom /= 1.1;

		// Recalcula offset para manter o ponto do mouse fixo
		t_complex new_mouse_complex = pixel_to_complex(fractal->mouse_x, fractal->mouse_y, fractal);
		fractal->offset_x += mouse_complex.real - new_mouse_complex.real;
		fractal->offset_y += mouse_complex.imag - new_mouse_complex.imag;
		render_fractal(fractal);
	}
}

void	close_hook(void *param)
{
	t_fractol	*fractal;

	fractal = (t_fractol *)param;
	mlx_close_window(fractal->mlx);
	exit(0);
}

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_fractol *fractal = (t_fractol *)param;

	(void)mods; // Não usado

	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			// Inicia o drag
			fractal->mouse_pressed = 1;
			fractal->last_mouse_x = fractal->mouse_x;
			fractal->last_mouse_y = fractal->mouse_y;
		}
		else if (action == MLX_RELEASE)
		{
			// Para o drag
			fractal->mouse_pressed = 0;
		}
	}
}

// 🆕 NOVO: Hook para movimento do cursor (implementa o drag)
void cursor_hook(double xpos, double ypos, void *param)
{
    t_fractol *fractal = (t_fractol *)param;

    // Atualiza posição atual do mouse
    fractal->mouse_x = (int)xpos;
    fractal->mouse_y = (int)ypos;

    // Se o mouse estiver pressionado, implementa o drag
    if (fractal->mouse_pressed)
    {
        // Calcula diferença de movimento
        int delta_x = fractal->mouse_x - fractal->last_mouse_x;
        int delta_y = fractal->mouse_y - fractal->last_mouse_y;

        // Converte movimento de pixels para movimento no plano complexo
        // Movimento é proporcional ao nível de zoom (mais zoom = movimento mais preciso)
        double move_factor = 4.0 / (fractal->width * fractal->zoom);
        fractal->offset_x -= delta_x * move_factor;
        fractal->offset_y -= delta_y * move_factor;

        // Atualiza última posição
        fractal->last_mouse_x = fractal->mouse_x;
        fractal->last_mouse_y = fractal->mouse_y;

        // Re-renderiza o fractal
        render_fractal(fractal);
    }
}
