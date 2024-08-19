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
    data->pixel = 10;
    data->speed = 3;
    data->map_s->map_height = 0;
    data->map_s->map_width = 0;
    data->img_s->celing = 0xADEAF8;
    data->img_s->floor = 0x4C585B;
    ft_read_map(data, file);
    ft_player_find(data);
    data->width = data->map_s->map_width * data->pixel;
    data->height = data->map_s->map_height * data->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
    data->img_s->mini_map = mlx_new_image(data->mlx, data->width, data->height);
    data->img_s->screen = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->img_s->addr = mlx_get_data_addr(data->img_s->mini_map, &data->img_s->bits_per_pixel, &data->img_s->line_length, &data->img_s->endian);
    data->img_s->s_addr = mlx_get_data_addr(data->img_s->screen, &data->img_s->s_bits_per_pixel, &data->img_s->s_line_length, &data->img_s->s_endian);
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