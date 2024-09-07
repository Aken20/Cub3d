#include "../Cub3d.h"


void    parse_view(t_map *map_data)
{
    t_vars vars;

    init_vars(&vars);
    vars.y = -1;
    while (map_data->map[++vars.y])
    {
        vars.x = -1;
        while (map_data->map[vars.y][++vars.x])
        {
            if (map_data->map[vars.y][vars.x] == 'N' || map_data->map[vars.y][vars.x] == 'S'
                || map_data->map[vars.y][vars.x] == 'W' || map_data->map[vars.y][vars.x] == 'E')
            {
                if (vars.y == 0 || vars.x == 0 || vars.y == map_data->height - 1)
                    exit_error("(Invalid view position)", map_data, NULL);
                if (vars.x > (int)ft_strlen(map_data->map[vars.y - 1]) || vars.x > (int)ft_strlen(map_data->map[vars.y + 1]))
                    exit_error("(Invalid view position)", map_data, NULL);
                if ((map_data->map[vars.y - 1][vars.x] != '1' && map_data->map[vars.y - 1][vars.x] != '0') 
                    || (map_data->map[vars.y + 1][vars.x] != '1' && map_data->map[vars.y + 1][vars.x] != '0')
                    || (map_data->map[vars.y][vars.x - 1] != '1' && map_data->map[vars.y][vars.x - 1] != '0')
                    || (map_data->map[vars.y][vars.x + 1] != '1' && map_data->map[vars.y][vars.x + 1] != '0'))
                    exit_error("(Invalid view position)", map_data, NULL);
            }
        }
    }
}


void check_duplicated_view_char(t_map *map_data)
{
    t_vars vars;

    vars.y = -1;
    vars.isviewfound = 0;
    while (map_data->map[++vars.y])
    {
        vars.x = -1;
        while (map_data->map[vars.y][++vars.x])
        {
            if (map_data->map[vars.y][vars.x] == 'N' || map_data->map[vars.y][vars.x] == 'S'
                || map_data->map[vars.y][vars.x] == 'W' || map_data->map[vars.y][vars.x] == 'E')
            {
                vars.isviewfound++;
                if (vars.isviewfound > 1)
                    exit_error("(Found duplicated view)", map_data, NULL);
            }
            else if (map_data->map[vars.y][vars.x] != '0' && map_data->map[vars.y][vars.x] != '1'
                && map_data->map[vars.y][vars.x] != ' ')
            {
                exit_error("(undefined character)", map_data, NULL);
            }
        }
    }
    if (vars.isviewfound != 1)
        exit_error("(No view found)", map_data, NULL);
}


int   valid_view_char(char c)
{
    if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
        return (0);
    return (1);
}
void check_surrounding(t_map *map_data)
{
    t_vars vars;

    vars.x = -1;
    vars.y = -1;
    while (map_data->map[++vars.y])
    {
        vars.x = -1;
        while (map_data->map[vars.y][++vars.x])
        {
            if (map_data->map[vars.y][vars.x] == '0')
            {
                if (vars.y == 0 || vars.x == 0 || vars.y == map_data->height - 1)
                    exit_error("(Invalid map)", map_data, NULL);
                if ((vars.x > (int)ft_strlen(map_data->map[vars.y - 1]) || vars.x > (int)ft_strlen(map_data->map[vars.y + 1])))
                    exit_error("(Invalid map)", map_data, NULL);
                if ((map_data->map[vars.y - 1][vars.x] != '1' && map_data->map[vars.y - 1][vars.x] != '0' && !valid_view_char(map_data->map[vars.y - 1][vars.x]))
                    || (map_data->map[vars.y + 1][vars.x] != '1' && map_data->map[vars.y + 1][vars.x] != '0' && !valid_view_char(map_data->map[vars.y + 1][vars.x]))
                    || (map_data->map[vars.y][vars.x - 1] != '1' && map_data->map[vars.y][vars.x - 1] != '0' && !valid_view_char(map_data->map[vars.y][vars.x - 1]))
                    || (map_data->map[vars.y][vars.x + 1] != '1' && map_data->map[vars.y][vars.x + 1] != '0' && !valid_view_char(map_data->map[vars.y][vars.x + 1])))
                    exit_error("(Invalid map)", map_data, NULL);
            }
        }
    }
}

void parsing_the_map(t_map *map_data)
{
    check_surrounding(map_data);
    check_duplicated_view_char(map_data);
    parse_view(map_data);
}