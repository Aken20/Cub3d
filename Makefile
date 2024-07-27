NAME = Cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar -rcs
RM = rm -f

FILES = main

# BFILES = map so_long readmap movment valid_map allocate enemy ft_fire

GNL = get_next_line/GNL.a
PRINTF = printf/printf.a
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

SRCS = $(addsuffix .c, $(FILES))
BSRCS = $(addsuffix _bonus.c, $(BFILES))

OBJS = $(addsuffix .o, $(FILES))
BOBJS = $(addsuffix _bonus.o, $(BFILES))

all: $(NAME)

$(GNL):
	make -C get_next_line
$(PRINTF):
	make -C printf
$(LIBFT):
	make -C libft
$(MLX):
	make -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

$(NAME): $(OBJS) $(PRINTF) $(GNL) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

# bonus: $(NAME)_bonus

# $(NAME)_bonus: $(BOBJS) $(PRINTF) $(GNL) $(LIBFT) $(MLX)
# 	$(CC) $(CFLAGS) $(BOBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) -framework OpenGL -framework AppKit -o $(NAME)_bonus

clean:
	make clean -C get_next_line
	make clean -C printf
	make clean -C libft
	make clean -C minilibx-linux
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME) $(NAME)_bonus $(PRINTF) $(GNL) $(MLX) $(LIBFT)

re: clean all

.PHONY: bonus all clean fclean re