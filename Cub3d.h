#ifndef _CUB3D_H_
# define _CUB3D_H_

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
    int     map_width;
    int     map_height;
	int		px;
	int		py;
	int		pixel;
	int		speed;
	double	angle;
	int		rx;
	int		ry;
}				t_map;

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
    int     celing;
    int     floor;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	double	r_angle;
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
void my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif