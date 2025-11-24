NAME = cub3D

SRCS =src/test.c \

OBJS        = $(SRCS:.c=.o)

# --- libft ---
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

# --- compiler ---
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
CPPFLAGS    = -I includes -I .
RM          = rm -f

all: $(NAME)

# build libft first
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

# build minishell
$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(LDFLAGS)

# compile .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# clean
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
