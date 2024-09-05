#ifndef CUB3D_H
# define CUB3D_H

# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <errno.h>
# include <stdbool.h>
# include "libft/libft.h"
# include <math.h>
# include "printf/ft_printf.h"
# include "libft/get_next_line.h"
# include "minilibx-linux/mlx.h"

# ifdef __linux__
	# define ESC 65307
	# define W 119
	# define S 115
	# define D 100
	# define A 97
# endif

# ifdef __APPLE__
	# define ESC 53
	# define W 13
	# define S 1
	# define D 2
	# define A 0
# endif


# define WIDTH 1280
# define HEIGHT 720
# define PI 3.14159265359


typedef struct s_img
{
	void	*img;
	char	*addr;
    int 	bits_per_pixel;
    int 	line_length;
    int 	endian;
}				t_img;

typedef struct s_map
{
	char	**map;
	int		px;
	int		p_x; // for testing
	int		p_y; // for testing
	int		p_s; // for testing
	int		x; // for testing
	int		y; // for testing
	int		py;
	int		pixel;
	int		speed;
	float	angle;
	int		rx;
	int		ry;
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
	t_img	*mini_map;
	t_img	*screen;
	t_img	*W_Wall;
	t_img	*E_Wall;
	t_img	*N_Wall;
	t_img	*S_Wall;
	void	*win;
	void	*mlx;
	int		width;
	int		height;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	float	r_angle;
}				t_data;

// main ---- file name: main.c ----

void extracting_the_map(t_map *map_data);

// Exution ---- file name: execution.c ----

int ft_hocks(int keycode, t_data *data);
int ft_render(t_data *data);
void get_width(t_data *data);
void ft_player_find(t_data *data);
bool ft_check_collision(t_data *data, int x, int y, int direction);
int ft_quit_game(t_data *data);
void draw_ray(t_data *data);
float d_to_r(float degree);
void draw_ray(t_data *data);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);


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
