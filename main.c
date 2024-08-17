# include "Cub3d.h"

void    ft_free_data(t_data *data)
{
    free(data->map_s);
    free(data->img_s);
    free(data);
}

t_data *ft_init(char *file)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->map_s = malloc(sizeof(t_map));
    data->img_s = malloc(sizeof(t_imgs));
    data->pixel = 30;
    data->speed = 5;
    data->map_s->map_width = 0;
    data->map_s->map_height = 0;
    ft_read_map(data, file);
    ft_player_find(data);
    data->width = data->map_s->map_width * data->pixel;
    data->height = data->map_s->map_height * data->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3d");
    data->img_s->img = mlx_new_image(data->mlx, data->width, data->height);
    data->img_s->addr = mlx_get_data_addr(data->img_s->img, &data->img_s->bits_per_pixel, &data->img_s->line_length, &data->img_s->endian);
    return (data);
}

int ft_quit_game(t_data *data)
{
    ft_free_data(data);
    exit(0);
}

int main(int ac, char **av)
{
    t_data *data;
    if (ac != 2)
    {
        printf("Error\n");
        exit(0);
    }
    data = ft_init(av[1]);
    mlx_loop_hook(data->mlx, ft_render, data);
    mlx_hook(data->win, 2, 1L<<0, ft_hocks, data);
    mlx_hook(data->win, 17, 1L<<0, ft_quit_game, data);
    mlx_loop(data->mlx);
}