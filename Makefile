# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpaulo-c <rpaulo-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 05:19:32 by rpaulo-c          #+#    #+#              #
#    Updated: 2025/06/06 06:34:16 by rpaulo-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = fractol

# Compiler and flags
CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra

# Directories
OBJ_DIR = obj
LIBFT_DIR = libs/libft
MLX_DIR = libs/MLX42

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/build/libmlx42.a

# Linker flags
MLX_FLAGS = -lX11 -lXext -lm -ldl -lglfw

# Source files
SRCS = colors.c \
		events.c \
		fractals.c \
		init.c \
		main.c \
		render.c \
		mouse_events.c \
		colors_schemes.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Header files (for dependencies)
HEADERS = fractol.h

# Colors for output
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

# Default rule
all: $(NAME)

# Create executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Compile object files
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MLX_DIR)/include -c $< -o $@
	@echo "$(GREEN)✓ Compiled: $<$(RESET)"

# Create obj directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)📁 Created $(OBJ_DIR) directory$(RESET)"

# Build libft
$(LIBFT):
	@echo "$(YELLOW)🔧 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ Libft built successfully!$(RESET)"

# Build MLX42
$(MLX):
	@echo "$(YELLOW)🔧 Building MLX42...$(RESET)"
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build; \
	fi
	@$(MAKE) -C $(MLX_DIR)/build -j4 --no-print-directory
	@echo "$(GREEN)✓ MLX42 built successfully!$(RESET)"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✗ Object files removed$(RESET)"
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory; \
	fi
	@if [ -d "$(MLX_DIR)/build" ]; then \
		$(MAKE) -C $(MLX_DIR)/build clean --no-print-directory 2>/dev/null || true; \
	fi

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then \
		$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory; \
	fi
	@rm -rf $(MLX_DIR)/build
	@echo "$(RED)✗ MLX42 build directory removed$(RESET)"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
