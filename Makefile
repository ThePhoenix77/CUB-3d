NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_MACOS = mlx_macos/libmlx.a
MLX_LINUX = mlx_linux/libmlx.a

INCLUDES = -Iinc

OS = $(shell uname -s)
ifeq ($(OS), Darwin)
	MLX = mlx_macos/libmlx.a
	LIBS = -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
else ifeq ($(OS), Linux)
	MLX = mlx_linux/libmlx.a
	LIBS = -Lmlx_linux -lmlx -lXext -lX11 -lm
else
	$(wa hasssssssssssssssan)
endif

SRCS_DIR = src
SRCS = $(wildcard $(SRCS_DIR)/*.c) $(wildcard $(SRCS_DIR)/*/*.c) $(SRCS_DIR)/main.c
OBJS = $(SRCS:.c=.o)
all: $(MLX) $(NAME)

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(MLX_MACOS):
	make -s -C mlx_macos
$(MLX_LINUX):
	make -s -C mlx_linux
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)


clean:
	make -s clean -C mlx_linux
	make -s clean -C mlx_macos
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re