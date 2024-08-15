#ifndef _CUB3D_H_
# define _CUB3D_H_

# include <stdbool.h>
# include "libft/libft.h"
# include <math.h>
# include "printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# define RA 123
# define LA 124
# define PI 3.14159265359

typedef struct s_imgs
{
	void	*W_Wall;
	void	*E_Wall;
	void	*N_Wall;
    void	*S_Wall;
	void	*img;
    int     C;
    int     F;
	char	*addr;
    int 	bits_per_pixel;
    int 	line_length;
    int 	endian;
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
	int		px;
	int		py;
	int		rx;
	int		ry;
	int		angle;
}				t_data;

int ft_hocks(int keycode, t_data *data);
int ft_render(t_data *data);
void ft_read_map(t_data *img, char *file);
void ft_player_find(t_data *data);
bool ft_check_collision(t_data *data, int x, int y, int direction);
int ft_quit_game(t_data *data);
void draw_ray(t_data *data);
float d_to_r(int degree);
void draw_ray(t_data *data);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif