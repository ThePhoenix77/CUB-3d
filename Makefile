NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_MACOS = mlx_macos/libmlx.a
MLX_LINUX = mlx_linux/libmlx.a

INCLUDES = -Iinc

OS = $(shell uname -s)
ifeq ($(OS), Darwin)
	INCLUDES += -Imlx_macos -Iinc/macos_inc
	MLX = $(MLX_MACOS)
	LIBS = -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
else ifeq ($(OS), Linux)
	INCLUDES += -Imlx_linux -Iinc/linux_inc
	MLX = $(MLX_LINUX)
	LIBS = -Lmlx_linux -lmlx -lXext -lX11 -lm
else
	$(error OS ma msupportich a hassssssssssssan)
endif

SRCS_DIR = src
OBJS_DIR = obj
SRCS = $(shell find $(SRCS_DIR) -type f -name "*.c")
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

all: $(MLX) $(NAME)


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(MLX_MACOS):
	make -s -C mlx_macos

$(MLX_LINUX):
	make -s -C mlx_linux
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	# make -s clean -C mlx_linux
	# make -s clean -C mlx_macos

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re




# 1.3457248783335231e-17 * 5.85 / 2.41e+03 

