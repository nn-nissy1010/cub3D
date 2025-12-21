# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/21 15:23:46 by nnishiya          #+#    #+#              #
#    Updated: 2025/12/21 20:41:35 by nnishiya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# ----------------------------------------
# Compiler
# ----------------------------------------
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
CPPFLAGS    = -I includes -I libft -I mlx -I .
RM          = rm -f

# ----------------------------------------
# Sources
# ----------------------------------------
SRCS = \
    src/main.c \
    src/init_game.c  \
    src/utils/free_split.c \
    src/parse/parse.c \
    src/parse/parse_utils.c \
    src/parse/parse_utils2.c \
    src/parse/parse_utils3.c \
    src/parse/map_builder.c \
    src/parse/map_validator.c \
    src/parse/spawn_objects.c \
    src/object/new_object.c \
    src/object/new_living.c \
    src/object/new_player.c \
    src/object/new_structure.c \
    src/texmgr/texmgr_init.c \
    src/texmgr/texmgr_destroy.c \
    src/render/draw_world.c \
    src/render/draw_wall.c \
	src/render/draw_utils.c \
    src/camera/camera_main.c \
    src/camera/ray_single.c \
    src/camera/ray_result.c \
    src/camera/handle_input.c \
    src/camera/run_dda.c \
    src/mlx_register/register_hooks.c

OBJS = $(SRCS:.c=.o)

# ----------------------------------------
# libft
# ----------------------------------------
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

# ----------------------------------------
# MiniLibX (Mac)
# ----------------------------------------
MLX_DIR     = mlx
MLX_LIB     = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# ----------------------------------------
# Build
# ----------------------------------------
all: $(NAME)

# libft build
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

# mlx build
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

# main build
$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

# compile .c → .o
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# ----------------------------------------
# Clean
# ----------------------------------------
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
