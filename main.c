# include "Cub3d.h"

void    ft_free_data(t_data *data)
{
    // free(data->map_s);
    free(data->mini_map);
    free(data->screen);
    free(data);
}

t_data *ft_init(t_map *map)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->mini_map = malloc(sizeof(t_img));
    data->screen = malloc(sizeof(t_img));
    data->map_s = map;
    data->map_s->pixel = 10;
    data->map_s->speed = 3;
    data->celing = 0xADEAF8;
    data->floor = 0x4C585B;
    ft_player_find(data);
    get_width(data);
    data->width = (data->map_s->height) * data->map_s->pixel;
    data->height = (data->map_s->height) * data->map_s->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
    data->mini_map->img = mlx_new_image(data->mlx, data->width, data->height);
    data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (!data->mini_map->img || !data->screen->img)
        exit_error("(Malloc failed)", data->map_s, NULL);
    data->mini_map->addr = mlx_get_data_addr(data->mini_map->img, &data->mini_map->bits_per_pixel, &data->mini_map->line_length, &data->mini_map->endian);
    data->screen->addr = mlx_get_data_addr(data->screen->img, &data->screen->bits_per_pixel, &data->screen->line_length, &data->screen->endian);
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
    mlx_loop_hook(data->mlx, ft_render, data);
    mlx_hook(data->win, 2, 1L<<0, ft_hocks, data);
    mlx_hook(data->win, 17, 1L<<0, ft_quit_game, data);
    mlx_loop(data->mlx);
    printf("PERFECTOO😘\n");
    return 0;
}
