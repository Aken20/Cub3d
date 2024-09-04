NAME = Cub3D
TEST_NAME = test_cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
AR = ar -rcs
RM = rm -f

FILES = main \
		./parsing/converting_colors \
		./parsing/free_va_arg \
		./parsing/parsing_colors \
		./parsing/parsing_map \
		./parsing/parsing_textures \
		./parsing/parsing_utils \
		./parsing/preparing_file_data \
		./parsing/space_chars_check \


TEST_FILES = main_test

# BFILES = map so_long readmap movment valid_map allocate enemy ft_fire

GNL = get_next_line/GNL.a
PRINTF = printf/printf.a
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

SRCS = $(addsuffix .c, $(FILES))
TEST_SRCS = $(addsuffix .c, $(TEST_FILES))
BSRCS = $(addsuffix _bonus.c, $(BFILES))

OBJS = $(addsuffix .o, $(FILES))
TEST_OBJS = $(addsuffix .o, $(TEST_FILES))
BOBJS = $(addsuffix _bonus.o, $(BFILES))

all: $(NAME)

$(GNL):
	make -C get_next_line

$(PRINTF):
	make -C printf

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS) $(PRINTF) $(GNL) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) -framework OpenGL -framework AppKit -o $(NAME)

test: $(TEST_OBJS) $(OBJS) $(PRINTF) $(GNL) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) -framework OpenGL -framework AppKit -o $(TEST_NAME)
	./$(TEST_NAME)

clean:
	make clean -C get_next_line
	make clean -C printf
	make clean -C libft
	make clean -C mlx
	$(RM) $(OBJS) $(BOBJS) $(TEST_OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME)_bonus $(TEST_NAME) $(PRINTF) $(GNL) $(MLX) $(LIBFT)

re: fclean all

.PHONY: test all clean fclean re
