# include "Cub3d.h"

t_data *ft_init(void)
{
    t_data *img;

    img = malloc(sizeof(t_data));
    img->map_s = malloc(sizeof(t_map));
    img->img_s = malloc(sizeof(t_imgs));
    img->size = 32;
    img->x = 0;
    img->y = 0;
    img->map_s->map = (char*[]) { "111111","100101","101001","1100N1","111111", NULL };
    img->map_s->map_width = 7;
    img->map_s->map_height = 6;
    return (img);
}

int main()
{
    t_data *img;

    img = ft_init();
    img->mlx = mlx_init();
    img->win = mlx_new_window(img->mlx, img->map_s->map_width * img->size, img->map_s->map_height * img->size, "Cub3d");
    // mlx_loop_hook(img->mlx, ft_render, img);
    // mlx_hook(img->win, 2, 0, ft_hocks, img);
    // mlx_hook(img->win, 17, 0, ft_quit_game, img);
    mlx_loop(img->mlx);}