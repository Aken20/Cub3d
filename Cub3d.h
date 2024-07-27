#ifndef _CUB3D_H_
# define _CUB3D_H_

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

typedef struct s_imgs
{
	void	*W_Wall;
	void	*E_Wall;
	void	*N_Wall;
    void	*S_Wall;
	void	*img;
    int     C;
    int     F;
}				t_imgs;

typedef struct s_map
{
	char	**map;
    int     map_width;
    int     map_height;
	int		p_x;
	int		p_y;
	int		p_dx;
	int		p_dy;
}				t_map;

typedef struct s_data
{
	t_map	*map_s;
	// t_map	*map_tmp;
	t_imgs	*img_s;
	void	*win;
	void	*mlx;
	int		width;
	int		height;
	int		pixel;
	int		speed;
	int		x;
	int		y;
}				t_data;

// int		ft_collectable_count(char **map);
// int		ft_check_map(t_data *img);
// int		ft_valid_path(t_data *img, int x, int y);
// void	ft_read_map(t_data *img, t_map *map, char *file);
// int		ft_firstline(char *map);
// int		ft_lastline(char *map, int len);
// void	ft_up(t_map *map_s, t_data *img);
// void	ft_down(t_map *map_s, t_data *img);
// void	ft_left(t_map *map_s, t_data *img);
// void	ft_right(t_map *map_s, t_data *img);
// int		ft_quit_game(t_data *img);
// int		ft_check_sides(char **map, int len);
// int		ft_exits(char **map);
// void	ft_handle(t_data *img, char c1, char c2, int i);
// int		ft_is_valid(char **map, int y, int x);
// void	*ft_allocate(t_data *img, char *file);
// void	ft_free_all(t_data *img, int k);
// int		ft_exit_count(char **map);
// void	ft_check_read(t_data *img, char *s, int fd);

#endif