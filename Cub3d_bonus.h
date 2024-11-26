/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:59:58 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/12 00:00:03 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
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
# include "libft/get_next_line.h"
# include "minilibx-linux/mlx.h"

# ifdef __linux__
#  define ZOOM_IN 61
#  define ZOOM_OUT 45
#  define ESC 65307
#  define RA 65363
#  define LA 65361
#  define SP 32
#  define W 119
#  define S 115
#  define D 100
#  define A 97
# endif

# ifdef __APPLE__
#  define ZOOM_IN 24
#  define ZOOM_OUT 27
#  define ESC 53
#  define RA 124
#  define LA 123
#  define SP 49
#  define W 13
#  define S 1
#  define D 2
#  define A 0
# endif

# define WIDTH 1280
# define HEIGHT 720
# define PI 3.14159265359

typedef struct s_keys
{
	bool		up;
	bool		zoom_in;
	bool		zoom_out;
	bool		down;
	bool		left;
	bool		right;
	bool		rotate_left;
	bool		rotate_right;
}				t_keys;

typedef struct s_img
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_ray
{
	float	x;
	float	y;
	float	distance;
	float	angle;
}				t_ray;

typedef struct s_map
{
	char	**map;
	float	px;
	float	py;
	int		pixel;
	int		speed;
	float	angle;
	float	rx;
	float	ry;
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
	int		floor;
	int		ceiling;
	int		width;
	int		height;
}				t_map;

typedef struct s_vars
{
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
	int			iscolorfound;
	int			txturecounter;
	int			isviewfound;
	char		*line;
	char		**splitted;
	char		*tmp;
}				t_vars;

typedef struct s_data
{
	t_map	*map;
	t_img	*mini_map;
	t_img	*mini_map_frame;
	t_img	*screen;
	t_img	*door[3];
	t_img	*flame[3];
	t_img	*w_wall;
	t_img	*e_wall;
	t_img	*n_wall;
	t_img	*s_wall;
	float	start;
	float	end;
	t_keys	keys;
	void	*win;
	void	*mlx;
	int		line_height;
	int		x_screen;
	int		width;
	int		height;
	int		mini_map_scale;
	int		door_flag;
	int		flame_flag;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	float	r_angle;
}				t_data;

// main ---- file name: main.c ----

void	extracting_the_map(t_map *map_data);

// Exution ---- file name: execution.c ----

void	ft_hocks(t_data *data);
void	set_player_to_zero(t_data *data);
int		ft_mouse_hocks(int x, int y, t_data *data);
int		ft_render(t_data *data);
void	get_width(t_data *data);
void	ft_player_find(t_data *data);
void	draw_minimap(t_data *data);
void	draw_screen(t_data *data);
void	ft_draw_player(t_data *data);
void	open_textures(t_data *data);
void	ft_free_data(t_data *data);
void	handel_door(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	ft_free_data(t_data *data);
int		ft_quit_game(t_data *data);
void	draw_ray(t_data *data);
void	draw_wall(t_data *data, bool is_vert, int line_height, t_img *img);
float	d_to_r(float degree);
int		wall_hit(float x, float y, t_data *data);
int		wall_hit_2(float x, float y, t_data *data);
float	get_vert_dest(t_data *data);
float	get_hor_dest(t_data *data);
void	draw_ray(t_data *data);
void	draw_textures(t_data *data, bool is_vert, int line_height);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		my_mlx_pixel_get(t_img *img, int x, int y);

// parsing ----- file name: preparing_file_data ----
void	init_struct(t_map *map, t_vars *vars);
void	exit_error(char *str, t_map *map, t_vars *vars);
void	check_map_extention(char *map_file);
void	fill_the_file(t_map *map_data, int len, char *map_file);
void	reading_the_file(t_map *map_data, char *map_file);
void	init_vars(t_vars *vars);

// parsing ----- file name: free_va_arg ----
void	free_2d(char ***ptr);
void	free_textures(t_map *map);
void	free_map_stuct(t_map *map);
void	free_vars_stuct(t_vars *vars);

// parsing ----- file name: space_chars_check ----

void	check_white_spaces(t_map *map_data);
void	check_only_spaces_map(t_map *map_data);
void	check_unwanted_chars(t_map *map_data);
int		ft_isspace(char c);

// parsing ----- file name: parsing_map_utils_bonus ----
void	check_duplicated_view_char(t_map *m_data);
// parsing ----- file name: parsing_extra_bonus ----

void	parsing_door_textures(t_map *map_data);
void	parsing_flame_textures(t_map *map_data);

// parsing ----- file name: parsing_textures ----
void	defining_textures(t_map *map_data);
void	parsing_textures(t_map *map_data);
void	check_duplicated_textures(t_map *map_data);
int		define_texture(char **splitted, t_map *map_data);

// parsing ----- file name: parsing_colors ----
void	defining_colors(t_map *map_data);
void	check_duplicated_colors(t_map *map_data);
void	parsing_colors(t_map *map_data);
int		define_colors(char *splitted, t_map *map_data, char c);

// parsing ----- file name: converting_colors ----

void	converting_colors(t_map *map_data, char *color, char c);
void	convert_the_color(t_map *map, char **splitted_color, char colortype);
void	checking_commas(t_map *map_data, char *color);

// parsing ----- file name: parsing_map ----
void	parsing_the_map(t_map *map_data);
void	check_surrounding(t_map *map_data, char c);
void	check_duplicated_view_char(t_map *map_data);
void	parse_view(t_map *map_data);
int		valid_view_char(char c);
int		valid_surrounding_char(char c);

// parsing ----- file name: parsing_utils ----

void	exit_error(char *str, t_map *map, t_vars *vars);
void	getting_the_height(t_map *map_data);
int		ft_strcmp(const char *s1, const char *s2);
int		valid_line_char(char c);
bool	check_line_value(char *line, t_vars *vars);
int		find_char_index(const char *str, char c);

#endif
