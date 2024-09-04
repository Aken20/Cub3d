#include "cub3d.h"


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

int main(int ac, char **av)
{
    t_map map;
    t_vars vars;

    if (ac != 2)
    {
        printf("Error\nInvalid number of arguments\n");
        exit(1);
    }
    init_struct(&map, &vars);
    check_map_extention(av[1]);
    reading_the_file(&map, av[1]);
    check_white_spaces(&map);
    check_unwanted_chars(&map);
    defining_textures(&map);
    parsing_textures(&map);
    defining_colors(&map);
    parsing_colors(&map);
    extracting_the_map(&map);
    parsing_the_map(&map);
    printf("PERFECTOO😘\n");
    return 0;
}
