# NAME = cub3D

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Ofast #-fsanitize=address

# MLX_MACOS = mlx_macos/libmlx.a
# MLX_LINUX = mlx_linux/libmlx.a

# INCLUDES = -Iinc

# OS = $(shell uname -s)
# ifeq ($(OS), Darwin)
# 	INCLUDES += -Imlx_macos -Iinc/macos_inc
# 	MLX = $(MLX_MACOS)
# 	LIBS = -Lmlx_macos -lmlx -framework OpenGL -framework AppKit -O3
# else ifeq ($(OS), Linux)
# 	INCLUDES += -Imlx_linux -Iinc/linux_inc
# 	MLX = $(MLX_LINUX)
# 	LIBS = -Lmlx_linux -lmlx -lXext -lX11 -lm
# else
# 	$(error Unsupported OS. Only Darwin and Linux are supported.)
# endif

# SRCS_DIR = src
# OBJS_DIR = obj
# SRCS = $(shell find $(SRCS_DIR) -type f -name "*.c")
# OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# all: $(NAME)

# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
# 	mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# $(MLX_MACOS):
# 	make -s -C mlx_macos

# $(MLX_LINUX):
# 	make -s -C mlx_linux

# $(NAME): $(OBJS) $(MLX)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# clean:
# 	rm -rf $(OBJS_DIR)
# 	# make -s clean mlx_linux
# 	# make -s clean mlx_macos

# fclean: clean
# 	rm -rf $(NAME)

# X:
# 	#clear

# re: fclean all X

# .PHONY: all clean fclean re



NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf

SRC = src/
OBJ := $(SRC:%.c=%.o)
SRC_BONUS = bonus/checker.c bonus/get_next_line_utils.c bonus/get_next_line.c bonus/instruction.c bonus/instruction2.c \
			bonus/instruction3.c bonus/parsing.c bonus/parsing2.c bonus/split.c bonus/utils.c bonus/utils2.c bonus/utils3.c

OBJ_BONUS := $(SRC_BONUS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJ): push_swap.h

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) -o $(NAME_BONUS)

$(OBJ_BONUS): bonus/checker.h

clean: 
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all