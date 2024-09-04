#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h> 
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

typedef struct s_imgs
{
	void	*wall;
	void	*player;
	void	*player_l;
	void	*player_r;
	void	*collectable;
	void	*exit;
	void	*closed_door;
}				t_imgs;

typedef struct s_map
{
	char	**map;
	char	**file;
	char	*south_txture;
	char	*north_txture;
	char	*east_txture;
	char	*west_txture;
	char	*floor_color;
	char	*ceiling_color;
	int		red;
	int		green;
	int		blue;
	int 	floor;
	int 	ceiling;
	int		width;
	int		height;
	int		y;
	int		x;
	int		p_y;
	int		p_x;
}				t_map;

typedef struct s_vars {
	int			i;
	int			j;
	int			k;
	int			l;
	int			len;
	int			m;
	int			n;
	int			x;
	int			c;
	int			y;
	int			fd;
	int			counter;
	int 		iscolorfound;
	int 		isviewfound;
	char 		*line;
	char 		**splitted;
	char		*tmp;
}               t_vars;

typedef struct s_data
{
	t_map	*map_s;
	t_map	*map_tmp;
	t_imgs	*img_s;
	void	*win;
	void	*mlx;
	int		size;
	int		moves;
	int		x;
	int		y;
}				t_data;


// main ---- file name: main.c ----

void extracting_the_map(t_map *map_data);


// parsing ----- file name: preparing_file_data ----
void	init_struct(t_map *map, t_vars *vars);
void	exit_error(char *str, t_map *map, t_vars *vars);
void	check_map_extention(char *map_file);
void	fill_the_file(t_map *map_data, int len, char *map_file);
void	reading_the_file(t_map *map_data, char *map_file);
void 	init_vars(t_vars *vars);

// parsing ----- file name: free_va_arg ----
void	free_all(int count, ...);
void	free_all_2d(int count, ...);
void	free_textures(t_map *map);
void	free_map_stuct(t_map *map);
void	free_vars_stuct(t_vars *vars);

// parsing ----- file name: space_chars_check ----

void	check_white_spaces(t_map *map_data);
void    check_only_spaces_map(t_map *map_data);
void	check_unwanted_chars(t_map *map_data);
int     ft_isspace(char c);


// parsing ----- file name: parsing_textures ----
void	defining_textures(t_map *map_data);
void	parsing_textures(t_map *map_data);
void	check_duplicated_textures(t_map *map_data);
int		define_texture(char **splitted, t_map *map_data);


// parsing ----- file name: parsing_colors ----
void	defining_colors(t_map *map_data);
void	check_duplicated_colors(t_map *map_data);
void	parsing_colors(t_map *map_data);
int		define_colors(char **splitted, t_map *map_data);

// parsing ----- file name: converting_colors ----

void	converting_colors(t_map *map_data, char *color, char c);
void    convert_the_color(t_map *map, char **splitted_color, char colortype);
void    checking_commas(t_map *map_data, char *color);

// parsing ----- file name: parsing_map ----
void	parsing_the_map(t_map *map_data);
void	check_surrounding(t_map *map_data);
void	check_duplicated_view_char(t_map *map_data);
void	parse_view(t_map *map_data);
int		valid_view_char(char c);


// parsing ----- file name: parsing_utils ----

void exit_error(char *str, t_map *map, t_vars *vars);
void getting_the_height(t_map *map_data);
int ft_strcmp(const char *s1, const char *s2);

// ----- end of parsing -----



#endif
