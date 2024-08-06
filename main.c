#include "Cub3d.h"


void exit_error(char *str)
{
    ft_printf("Error\n%s\n", str);
    exit(1);
}

void init_struct(t_map *map, t_vars *vars)
{
    map->p_x = 0;
    map->p_y = 0;
    map->p_s = 0;
    map->x = 0;
    map->y = 0;
    vars->i = 0;
    vars->j = 0;
    vars->k = 0;
    vars->l = 0;
    vars->m = 0;
    vars->n = 0;
    map->map = NULL;
    vars->line = NULL;
    vars->tmp = NULL;
}

void check_map_extention(char *map_file)
{
    int i;

    i = 0;
    while (map_file[i])
        i++;
    if ( map_file[i - 5] == '/' || i == 4)
        exit_error("(No file name found)");
    if (ft_strncmp(&map_file[i - 4], ".cub", 4) != 0)
        exit_error("(Invalid file extention)");
}

void fill_the_map(t_map *map_data, int i, char *map_file)
{
    t_vars vars;

    vars.fd = open(map_file, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor)");
    map_data->map = (char **)malloc(sizeof(char *) * (i + 1));
    if (!map_data->map)
        exit_error("(Malloc failed)");
    vars.line = get_next_line(vars.fd);
    vars.i = 0;
    while (vars.line)
    {
        map_data->map[vars.i] = ft_strdup(vars.line);
        free(vars.line);
        vars.line = get_next_line(vars.fd);
        vars.i++;
    }
    map_data->map[vars.i] = NULL;
    vars.i = 0;
    printf("here is the map\n");
    while (map_data->map[vars.i])
    {
        printf("%s\n", map_data->map[vars.i]);
        vars.i++;
    }
    close(vars.fd);
}


void read_map(t_map *map_data, char *map_file)
{
    t_vars vars;

    check_map_extention(map_file);
    vars.fd = open(map_file, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor)");
    vars.line = get_next_line(vars.fd);
    vars.i = -1;
    while (vars.line)
    {
        vars.i++;
        free(vars.line);
        vars.line = get_next_line(vars.fd);
    }
    free(vars.line);
    close(vars.fd);
    fill_the_map(map_data, vars.i, map_file);
}

void parse_the_map(t_map *map_data)
{
    (void)map_data;
    printf("parsing in the process\n");
}

// int main(int ac, char **av)
// {
//     t_map map;
//     t_vars vars;

//     if (ac != 2)
//     {
//         printf("Error\nInvalid number of arguments\n");
//         exit(1);
//     }
//     init_struct(&map, &vars);
//     read_map(&map, av[1]);
//     parse_the_map(&map);
//     // while(1)
//     // {
//         printf("Hello World\n");
//     // }
    

//     return 0;
// }