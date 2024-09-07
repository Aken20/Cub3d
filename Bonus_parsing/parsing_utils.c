#include "../Cub3d.h"


int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


void getting_the_height(t_map *map_data)
{
    t_vars vars;

    vars.x = -1;
    vars.y = -1;
    map_data->width = 0;
    map_data->height = 0;
    while (map_data->file[++vars.x])
    {
        if (map_data->file[vars.x][0] == '1' || map_data->file[vars.x][0] == ' ')
            map_data->height++;
    }    
}


void exit_error(char *str, t_map *map, t_vars *vars)
{
    free_map_stuct(map);
    free_vars_stuct(vars);
    ft_printf("Error\n%s\n", str);
    exit(1);
}