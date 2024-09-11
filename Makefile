NAME = cub3d
BONUS_NAME = cub3d_bonus
TEST_NAME = test_cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
AR = ar -rcs
RM = rm -f

FILES = main \
		./Execution/map \
		./Execution/textures \
		./Execution/movement \
		./Execution/ray \
		./Execution/ray_helper \
		./Execution/render \
		./parsing/converting_colors \
		./parsing/free_va_arg \
		./parsing/parsing_colors \
		./parsing/parsing_map \
		./parsing/parsing_textures \
		./parsing/parsing_utils \
		./parsing/parsing_map_utils \
		./parsing/preparing_file_data \
		./parsing/space_chars_check \

BONUS_FILES = main_bonus \
		./Bonus_Execution/textures_bonus \
		./Bonus_Execution/ray_bonus \
		./Bonus_Execution/map_bonus  \
		./Bonus_Execution/render_bonus \
		./Bonus_Execution/movement_bonus \
		./Bonus_Execution/ray_bonus_helper \
		./Bonus_Execution/ray_bonus_helper_2 \
		./Bonus_Execution/render_bonus_helper \
		./Bonus_Execution/movement_bonus_helper \
		./Bonus_parsing/converting_colors_bonus \
		./Bonus_parsing/free_va_arg_bonus \
		./Bonus_parsing/parsing_map_bonus \
		./Bonus_parsing/parsing_map_utils \
		./Bonus_parsing/parsing_utils_bonus \
		./Bonus_parsing/parsing_extra_bonus \
		./Bonus_parsing/parsing_colors_bonus \
		./Bonus_parsing/parsing_textures_bonus \
		./Bonus_parsing/space_chars_check_bonus \
		./Bonus_parsing/preparing_file_data_bonus \

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
BSRCS = $(addsuffix .c, $(BONUS_FILES))

OBJS = $(addsuffix .o, $(FILES))
TEST_OBJS = $(addsuffix .o, $(TEST_FILES))
BOBJS = $(addsuffix .o, $(BONUS_FILES))

%.o: %.c
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

all: $(NAME)

bonus: $(BONUS_NAME)

$(PRINTF):
	make -C printf

$(LIBFT):
	make -C libft

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(BONUS_NAME): $(BOBJS) $(PRINTF) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(BOBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(MLX_FLAGS) -o $(BONUS_NAME)


clean:
	make clean -C printf
	make clean -C libft
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS) $(BOBJS)

fclean:
	make clean
	$(RM) $(NAME) $(BONUS_NAME) $(PRINTF) $(MLX) $(LIBFT)

re:
	make fclean
	make all

.PHONY: test all clean fclean re
