# include "Cub3d_bonus.h"

void    ft_free_data(t_data *data)
{
    free(data->screen);
    free(data->W_Wall);
    free(data->E_Wall);
    free(data->N_Wall);
    free(data->S_Wall);
    free(data->door[0]);
    free(data->door[1]);
    free(data->door[2]);
    free(data->door[3]);
    mlx_destroy_window(data->mlx, data->win);
    free(data);
}

void    open_textures(t_data *data)
{
    data->screen = malloc(sizeof(t_img));
    data->door[0] = malloc(sizeof(t_img));
    data->door[1] = malloc(sizeof(t_img));
    data->door[2] = malloc(sizeof(t_img));
    data->door[3] = malloc(sizeof(t_img));
    data->W_Wall = malloc(sizeof(t_img));
    data->E_Wall = malloc(sizeof(t_img));
    data->N_Wall = malloc(sizeof(t_img));
    data->S_Wall = malloc(sizeof(t_img));
    data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->W_Wall->width = 800;
    data->W_Wall->height = 800;
    data->E_Wall->width = 800;
    data->E_Wall->height = 800;
    data->N_Wall->width = 800;
    data->N_Wall->height = 800;
    data->S_Wall->width = 800;
    data->S_Wall->height = 800;
    data->door[0]->img = mlx_xpm_file_to_image(data->mlx, "texture/door_1.xpm", &(data->door[0]->width), &(data->door[0]->height));
    data->door[1]->img = mlx_xpm_file_to_image(data->mlx, "texture/door_2.xpm", &(data->door[1]->width), &(data->door[1]->height));
    data->door[2]->img = mlx_xpm_file_to_image(data->mlx, "texture/door_3.xpm", &(data->door[2]->width), &(data->door[2]->height));
    data->door[3]->img = mlx_xpm_file_to_image(data->mlx, "texture/door_4.xpm", &(data->door[3]->width), &(data->door[3]->height));
    data->W_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->west_txture, &(data->W_Wall->width), &(data->W_Wall->height));
    data->E_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->east_txture, &(data->E_Wall->width), &(data->E_Wall->height));
    data->N_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->north_txture, &(data->N_Wall->width), &(data->N_Wall->height));
    data->S_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->south_txture, &(data->S_Wall->width), &(data->S_Wall->height));
    if (!data->W_Wall->img || !data->E_Wall->img || !data->N_Wall->img || !data->S_Wall->img || !data->screen->img
        || !data->door[0]->img|| !data->door[1]->img|| !data->door[2]->img|| !data->door[3]->img)
        exit_error("(Malloc failed)", data->map, NULL);
}

t_data *ft_init(t_map *map)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->map = map;
    data->map->pixel = 800;
    data->map->speed = 400;
    ft_player_find(data);
    get_width(data);
    data->width = (data->map->width) * data->map->pixel;
    data->height = (data->map->height) * data->map->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
    open_textures(data);
    data->door_flag = 0;
    data->door[0]->addr = mlx_get_data_addr(data->door[0]->img, &data->door[0]->bits_per_pixel, &data->door[0]->line_length, &data->door[0]->endian);
    data->door[1]->addr = mlx_get_data_addr(data->door[1]->img, &data->door[1]->bits_per_pixel, &data->door[1]->line_length, &data->door[1]->endian);
    data->door[2]->addr = mlx_get_data_addr(data->door[2]->img, &data->door[2]->bits_per_pixel, &data->door[2]->line_length, &data->door[2]->endian);
    data->door[3]->addr = mlx_get_data_addr(data->door[3]->img, &data->door[3]->bits_per_pixel, &data->door[3]->line_length, &data->door[3]->endian);
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
    mlx_loop_hook(data->mlx, ft_render, data);
    mlx_hook(data->win, 2, 1L<<0, ft_hocks, data);
    mlx_hook(data->win, 6, 1L<<6, ft_mouse_hocks, data);
    mlx_hook(data->win, 17, 1L<<0, ft_quit_game, data);
    mlx_loop(data->mlx);
    return 0;
}
