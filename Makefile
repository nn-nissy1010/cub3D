NAME = cub3D

# ----------------------------------------
# Sources
# ----------------------------------------
SRCS = \
    src/main.c \
    src/parse/parse.c \
    src/parse/parse_utils.c \
    src/parse/map_builder.c \
    src/parse/map_validator.c \
    src/parse/spawn_objects.c \
    src/object/new_object.c \
    src/object/new_living.c \
    src/object/new_player.c \
    src/object/new_door.c \
    src/object/new_structure.c \
    src/texmgr/texmgr_init.c \
    src/texmgr/texmgr_destroy.c \
    src/render/draw_world.c \

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
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# ----------------------------------------
# Compiler
# ----------------------------------------
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
CPPFLAGS = -I includes -I libft -I mlx -I .
RM          = rm -f

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

COMMON_OBJS = \
    src/utils/free_split.o

PARSER_OBJS = \
    src/parser_cli/main.o \
    src/init_game.o \
    src/parse/parse.o \
    src/parse/parse_utils.o \
    src/parse/map_builder.o \
    src/parse/map_validator.o \
    src/parse/spawn_objects.o \
    src/object/new_object.o \
    src/object/new_living.o \
    src/object/new_player.o \
    src/object/new_door.o \
    src/object/new_structure.o

parser_cli: $(PARSER_OBJS) $(COMMON_OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o parser_cli $(PARSER_OBJS) $(COMMON_OBJS) libft/libft.a

parser_cli_clean:
	rm -f $(COMMON_OBJS) $(PARSER_OBJS)

PARSER_JSON = \
    src/parse_json/main.o \
	src/parse/parse.o \
    src/parse/parse_utils.o \
    src/parse/map_builder.o \
    src/parse/map_validator.o \
    src/parse/spawn_objects.o \
    src/object/new_object.o \
    src/object/new_living.o \
    src/object/new_player.o \
    src/object/new_door.o \
    src/object/new_structure.o \
	src/render/draw_world.o \
	src/texmgr/texmgr_init.o \
	src/texmgr/texmgr_destroy.o \
	src/utils/free_split.o \


parser_json: $(LIBFT_LIB) $(MLX_LIB) $(PARSER_JSON)
	$(CC) $(CFLAGS) -o parser_json $(PARSER_JSON) $(LIBFT_LIB) $(MLX_FLAGS)

parser_json_clean:
	rm -f $(PARSER_JSON)
