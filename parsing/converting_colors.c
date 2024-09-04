#include "../Cub3d.h"


void    checking_commas(t_map *map_data, char *color)
{
    t_vars vars;

    vars.i = -1;
    vars.c = 0;
    vars.counter = 0;
    vars.len = ft_strlen(color);
    if (!color)
        exit_error("(Invalid color code)", map_data, NULL);
    while (color[++vars.i]) 
    {
        if (color[0] == ',')
            exit_error("(unexpected comma (color code))", map_data, NULL);
        if (color[vars.len - 1] == ',')
            exit_error("(Invalid color code)", map_data, NULL);
        if (color[vars.i] == ',')
        {
            if (color[vars.i + 1] == ',')
                exit_error("(found commas next to each other)", map_data, NULL);
            vars.counter++;
        }
    }
    if (vars.counter != 2)
        exit_error("(invalid color code)", map_data, NULL);
}


void    convert_the_color(t_map *map, char **splitted_color, char colortype)
{
    t_vars vars;

    init_vars(&vars);
    vars.i = -1;
    while (splitted_color[++vars.i])
    {
        if (ft_atoi(splitted_color[vars.i]) > 255 || ft_atoi(splitted_color[vars.i]) < 0)
        {
            free(splitted_color);
            exit_error("(valid code per decimal place is between 0 and 255 )", map, &vars);
        } 
    }
    map->red = ft_atoi(splitted_color[0]);
    map->green = ft_atoi(splitted_color[1]);
    map->blue = ft_atoi(splitted_color[2]);
    if (colortype == 'f')
        map->floor = (map->red << 16) | (map->green << 8) | map->blue;
    if (colortype == 'c')
        map->ceiling = (map->red << 16) | (map->green << 8) | map->blue;
}


void converting_colors(t_map *map_data, char *color, char colortype)
{
    t_vars vars;

    init_vars(&vars);
    vars.i = -1;
    vars.splitted = ft_split(color, ',');
    if (!vars.splitted)
        exit_error("(color code is missing)", map_data, &vars);
    while (vars.splitted[++vars.i])
    {
        vars.j = -1;
        while (vars.splitted[vars.i][++vars.j])
        {
            if (!ft_isdigit(vars.splitted[vars.i][vars.j]))
                exit_error("(color code is not a number)", map_data, &vars);
        }
    }
    convert_the_color(map_data, vars.splitted, colortype);
}

