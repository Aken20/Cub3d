#include "../Cub3d.h"

void    parsing_colors(t_map *map_data)
{
    checking_commas(map_data, map_data->floor_color);
    checking_commas(map_data, map_data->ceiling_color);
    converting_colors(map_data, map_data->floor_color, 'f');
    converting_colors(map_data, map_data->ceiling_color, 'c');
}

int define_colors(char **splitted, t_map *map_data)
{
    if (splitted[0][0] == 'F' && !map_data->floor_color)
    {
        if (map_data->floor_color && (ft_strncmp(map_data->floor_color , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated color)", map_data, NULL);
        return (map_data->floor_color = ft_strdup(splitted[1]), 1);
    }
    else if (splitted[0][0] == 'C' && !map_data->ceiling_color)
    {
        if (map_data->ceiling_color && (ft_strncmp(map_data->ceiling_color , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated color)", map_data, NULL);
        return (map_data->ceiling_color = ft_strdup(splitted[1]), 1);
    }
    return (0);
}

void check_duplicated_colors(t_map *map_data)
{
    t_vars vars;

    vars.x = -1;
    vars.counter = 0;
    while (map_data->file[++vars.x])
    {
        if (map_data->file[vars.x][0] == 'F' || map_data->file[vars.x][0] == 'C')
        {
            vars.splitted = ft_split(map_data->file[vars.x], ' ');
            if (!vars.splitted[0] ||  !vars.splitted[1])
                exit_error("(invalid color)", map_data, NULL);
            vars.counter++;
            free_2d(&vars.splitted);
        }
        if (vars.counter > 2)
            exit_error("(found duplicated color)", map_data, NULL);
    }
}

void defining_colors(t_map *map_data)
{
    t_vars vars;

    vars.x = -1;
    vars.iscolorfound = 0;
    check_duplicated_colors(map_data);
    while (map_data->file[++vars.x] && vars.iscolorfound != 2)
    {
        if ((map_data->file[vars.x][0] == 'C' || map_data->file[vars.x][0] == 'F') 
            && (map_data->file[vars.x][1] == ' ' && map_data->file[vars.x][2] != ' '))
        {
            vars.splitted = ft_split(map_data->file[vars.x], ' ');
            vars.iscolorfound += define_colors(vars.splitted, map_data);
            free_2d(&vars.splitted);
        }
        else if ((map_data->file[vars.x][0] == '1' || map_data->file[vars.x][0] == '0'))
            exit_error("(Invalid color or no color found)", map_data, NULL);
    }
    if (vars.iscolorfound != 2)
        exit_error("(Invalid color or no color found)", map_data, NULL);
}
