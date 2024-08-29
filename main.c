# include "Cub3d.h"

void    ft_free_data(t_data *data)
{
    free(data->map_s);
    free(data->mini_map);
    free(data->screen);
    free(data);
}

t_data *ft_init(char *file)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->map_s = malloc(sizeof(t_map));
    data->mini_map = malloc(sizeof(t_img));
    data->screen = malloc(sizeof(t_img));
    data->map_s->pixel = 10;
    data->map_s->speed = 3;
    data->map_s->map_height = 0;
    data->map_s->map_width = 0;
    data->celing = 0xADEAF8;
    data->floor = 0x4C585B;
    ft_read_map(data, file);
    ft_player_find(data);
    data->width = (data->map_s->map_width) * data->map_s->pixel;
    data->height = (data->map_s->map_height) * data->map_s->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
    data->mini_map->img = mlx_new_image(data->mlx, data->width, data->height);
    data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->mini_map->addr = mlx_get_data_addr(data->mini_map->img, &data->mini_map->bits_per_pixel, &data->mini_map->line_length, &data->mini_map->endian);
    data->screen->addr = mlx_get_data_addr(data->screen->img, &data->screen->bits_per_pixel, &data->screen->line_length, &data->screen->endian);
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
        exit(1);
    }
    data = ft_init(av[1]);
    mlx_loop_hook(data->mlx, ft_render, data);
    mlx_hook(data->win, 2, 1L<<0, ft_hocks, data);
    mlx_hook(data->win, 17, 1L<<0, ft_quit_game, data);
    mlx_loop(data->mlx);
}