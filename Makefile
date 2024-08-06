NAME = Cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

FILES = main

# BFILES = map so_long readmap movment valid_map allocate enemy ft_fire

GNL = get_next_line/GNL.a
PRINTF = printf/printf.a
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

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
	make -C mlx

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS) $(PRINTF) $(GNL) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) -framework OpenGL -framework AppKit -o $(NAME)

# bonus: $(NAME)_bonus

# $(NAME)_bonus: $(BOBJS) $(PRINTF) $(GNL) $(LIBFT) $(MLX)
# 	$(CC) $(CFLAGS) $(BOBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX) -framework OpenGL -framework AppKit -o $(NAME)_bonus

clean:
	make clean -C get_next_line
	make clean -C printf
	make clean -C libft
	make clean -C mlx
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME) $(NAME)_bonus $(PRINTF) $(GNL) $(MLX) $(LIBFT)

re: clean all

.PHONY: bonus all clean fclean re