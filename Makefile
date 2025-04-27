NAME = fractol

CC = cc

C_FLAGS = -g3 -Wall -Werror -Wextra

MLX_DIR = libs/MLX42

MLX = $(MLX_DIR)/build/libmlx42.a


MLX_FLAGS = -lX11 -lXext -lm -ldl -lglfw

SRC = main.c window.c julia.c mandelbrot.c

OBJ = $(SRC:.c=.o)


all : $(NAME)

$(MLX):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(NAME) : $(OBJ) $(MLX)
	$(CC) $(C_FLAGS) $(OBJ) $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
	@make clean -C $(MLX_DIR)/build

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	rm -rf $(MLX_DIR)/build

re: fclean all

.PHONY: all clean fclean re
