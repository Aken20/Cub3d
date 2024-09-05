# include "Cub3d.h"

void    ft_free_data(t_data *data)
{
    // free(data->map);
    free(data->mini_map);
    free(data->screen);
    free(data);
}

void    open_textures(t_data *data)
{
    data->mini_map = malloc(sizeof(t_img));
    data->screen = malloc(sizeof(t_img));
    data->W_Wall = malloc(sizeof(t_img));
    data->E_Wall = malloc(sizeof(t_img));
    data->N_Wall = malloc(sizeof(t_img));
    data->S_Wall = malloc(sizeof(t_img));
    data->mini_map->img = mlx_new_image(data->mlx, data->width, data->height);
    data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->W_Wall->width = 800;
    data->W_Wall->height = 800;
    data->E_Wall->width = 800;
    data->E_Wall->height = 800;
    data->N_Wall->width = 800;
    data->N_Wall->height = 800;
    data->S_Wall->width = 800;
    data->S_Wall->height = 800;
    data->W_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->west_txture, &(data->W_Wall->width), &(data->W_Wall->height));
    data->E_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->east_txture, &(data->E_Wall->width), &(data->E_Wall->height));
    data->N_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->north_txture, &(data->N_Wall->width), &(data->N_Wall->height));
    data->S_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->south_txture, &(data->S_Wall->width), &(data->S_Wall->height));
    if (!data->W_Wall->img || !data->E_Wall->img || !data->N_Wall->img || !data->S_Wall->img || !data->mini_map->img || !data->screen->img)
        exit_error("(Malloc failed)", data->map, NULL);
    // printf("ll: (%d)\n", my_mlx_pixel_get(data->E_Wall, 10, 10));
}

t_data *ft_init(t_map *map)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->mini_map = malloc(sizeof(t_img));
    data->screen = malloc(sizeof(t_img));
    data->map = map;
    data->map->pixel = 10;
    data->map->speed = 3;
    data->map->ceiling = 0xADEAF8;
    data->map->floor = 0x4C585B;
    ft_player_find(data);
    get_width(data);
    data->width = (data->map->width) * data->map->pixel;
    data->height = (data->map->height) * data->map->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
    open_textures(data);
    data->mini_map->addr = mlx_get_data_addr(data->mini_map->img, &data->mini_map->bits_per_pixel, &data->mini_map->line_length, &data->mini_map->endian);
    data->screen->addr = mlx_get_data_addr(data->screen->img, &data->screen->bits_per_pixel, &data->screen->line_length, &data->screen->endian);
    data->E_Wall->addr = mlx_get_data_addr(data->E_Wall->img, &data->E_Wall->bits_per_pixel, &data->E_Wall->line_length, &data->E_Wall->endian);
    data->W_Wall->addr = mlx_get_data_addr(data->W_Wall->img, &data->W_Wall->bits_per_pixel, &data->W_Wall->line_length, &data->W_Wall->endian);
    data->N_Wall->addr = mlx_get_data_addr(data->N_Wall->img, &data->N_Wall->bits_per_pixel, &data->N_Wall->line_length, &data->N_Wall->endian);
    data->S_Wall->addr = mlx_get_data_addr(data->S_Wall->img, &data->S_Wall->bits_per_pixel, &data->S_Wall->line_length, &data->S_Wall->endian);
    return (data);
}

int ft_quit_game(t_data *data)
{
    ft_free_data(data);
    exit(0);
}

void extracting_the_map(t_map *map_data)
{
    t_vars vars;

    getting_the_height(map_data);
    vars.x = -1;
    vars.y = -1;
    map_data->map = (char **)malloc(sizeof(char *) * (map_data->height + 1));
    if (!map_data->map)
        exit_error("(Malloc failed)", map_data, NULL);
    while (map_data->file[++vars.x])
    {
        if (map_data->file[vars.x][0] == '1' || (map_data->file[vars.x][0] == ' ')
            || map_data->file[vars.x][0] == '0')
        {
            vars.y++;
            map_data->map[vars.y] = ft_strdup(map_data->file[vars.x]);
        }
    }
    map_data->map[vars.y + 1] = NULL;
    
}

static void parsing(t_map *map, t_vars *vars, char **av) 
{
    init_struct(map, vars);
    check_map_extention(av[1]);
    reading_the_file(map, av[1]);
    check_white_spaces(map);
    check_unwanted_chars(map);
    defining_textures(map);
    parsing_textures(map);
    defining_colors(map);
    parsing_colors(map);
    extracting_the_map(map);
    parsing_the_map(map);
}

int main(int ac, char **av)
{
    t_data *data;
    t_map map;
    t_vars vars;

    if (ac != 2)
    {
        printf("Error\nInvalid number of arguments\n");
        exit(1);
    }
    parsing(&map, &vars, av);
    data = ft_init(&map);
    ft_render(data);
    // mlx_loop_hook(data->mlx, ft_render, data);
    mlx_hook(data->win, 2, 1L<<0, ft_hocks, data);
    mlx_hook(data->win, 17, 1L<<0, ft_quit_game, data);
    mlx_loop(data->mlx);
    printf("PERFECTOO😘\n");
    return 0;
}
