#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
#include <stdarg.h>
#include <stdlib.h>
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
	int 	floor;
	int 	ceiling;
	int		p_x;
	int		p_y;
	int		p_s;
	int		x;
	int		y;
}				t_map;

typedef struct s_vars {
	int			i;
	int			j;
	int			k;
	int			l;
	int			m;
	int			n;
	int			x;
	int			y;
	int			fd;
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

// Function prototypes
void	init_struct(t_map *map, t_vars *vars);
void	exit_error(char *str, t_map *map, t_vars *vars);
void	check_map_extention(char *map_file);
void	fill_the_map(t_map *map_data, int i, char *map_file);
void	read_map(t_map *map_data, char *map_file);
void	parse_the_map(t_map *map_data);

// Other functions
int		ft_collectable_count(char **map);
int		ft_check_map(t_data *img);
int		ft_valid_path(t_data *img, int x, int y);
void	ft_read_map(t_data *img, t_map *map, char *file);
int		ft_firstline(char *map);
int		ft_lastline(char *map, int len);
void	ft_up(t_map *map_s, t_data *img);
void	ft_down(t_map *map_s, t_data *img);
void	ft_left(t_map *map_s, t_data *img);
void	ft_right(t_map *map_s, t_data *img);
int		ft_quit_game(t_data *img);
int		ft_check_sides(char **map, int len);
int		ft_exits(char **map);
void	ft_handle(t_data *img, char c1, char c2, int i);
int		ft_is_valid(char **map, int y, int x);
void	*ft_allocate(t_data *img, char *file);
void	ft_free_all(t_data *img, int k);
int		ft_exit_count(char **map);
void	ft_check_read(t_data *img, char *s, int fd);

#endif
