NAME = Cub3D
TEST_NAME = test_cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
AR = ar -rcs
RM = rm -f

FILES = main \
		./Execution/map \
		./Execution/movement \
		./Execution/ray \
		./Execution/render \
		./parsing/converting_colors \
		./parsing/free_va_arg \
		./parsing/parsing_colors \
		./parsing/parsing_map \
		./parsing/parsing_textures \
		./parsing/parsing_utils \
		./parsing/preparing_file_data \
		./parsing/space_chars_check \


TEST_FILES = main_test

PRINTF = printf/printf.a
LIBFT = libft/libft.a

ifeq ($(shell uname), Linux)
	MLX_DIR = minilibx-linux
	MLX = minilibx-linux/libmlx_Linux.a
	MLX_FLAGS = -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz
	OBJ_FLAGS = -I/usr/include -Iminilibx-linux -O3
endif
ifeq ($(shell uname), Darwin)
	MLX_DIR = mlx
	MLX = mlx/libmlx.a
	MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
	OBJ_FLAGS = -Imlx
endif

SRCS = $(addsuffix .c, $(FILES))
TEST_SRCS = $(addsuffix .c, $(TEST_FILES))
BSRCS = $(addsuffix _bonus.c, $(BFILES))

OBJS = $(addsuffix .o, $(FILES))
TEST_OBJS = $(addsuffix .o, $(TEST_FILES))
BOBJS = $(addsuffix _bonus.o, $(BFILES))

all: $(NAME)

$(PRINTF):
	make -C printf

$(LIBFT):
	make -C libft

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
	# make clean -C get_next_line
	make clean -C printf
	make clean -C libft
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS) $(BOBJS)

fclean:
	make clean
	$(RM) $(NAME) $(NAME)_bonus $(PRINTF) $(MLX) $(LIBFT)

re:
	make fclean
	make all

.PHONY: test all clean fclean re
