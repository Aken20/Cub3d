#include "Cub3d.h"

void free_all(int count, ...)
{
    va_list args;
    void **ptr;
    int i = -1; 

    va_start(args, count);
    while (++i < count)
    {
        ptr = va_arg(args, void **);
        if (*(ptr))
        {
            free(*(ptr));
            *(ptr) = NULL;
        }
    }
    va_end(args);
}


void free_all_2d(int count, ...)
{
    va_list args;
    void ***ptr;
    int i, j;

    va_start(args, count);
    for (i = 0; i < count; i++)
    {
        ptr = va_arg(args, void ***);
        if (ptr && *ptr)
        {
            j = 0;
            while ((*ptr)[j])
            {
                free((*ptr)[j]);
                j++;
            }
            free(*ptr);
            *ptr = NULL;
        }
    }
    va_end(args);
}

void free_textures(t_map *map)
{
    if (!map)
        return;
    free_all(6, &map->north_txture, &map->south_txture,
        &map->east_txture, &map->west_txture,
        &map->floor_color, &map->ceiling_color);
}

void free_map_stuct(t_map *map)
{
    if (!map)
        return;
    free_textures(map);
    free_all_2d(2, &map->map, &map->file);
}

void free_vars_stuct(t_vars *vars)
{
    if (!vars)
        return;
    free_all(2, &vars->line, &vars->tmp);
    free_all_2d(1, &vars->splitted);
}

void exit_error(char *str, t_map *map, t_vars *vars)
{
    free_map_stuct(map);
    free_vars_stuct(vars);
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
    map->map = NULL;
    map->file = NULL;
    map->south_txture = NULL;
    map->north_txture = NULL;
    map->east_txture = NULL;
    map->west_txture = NULL;
    map->floor_color = NULL;
    map->ceiling_color = NULL;
    vars->i = 0;
    vars->j = 0;
    vars->k = 0;
    vars->l = 0;
    vars->m = 0;
    vars->n = 0;
    vars->line = NULL;
    vars->tmp = NULL;
    vars->splitted = NULL;
}

void check_map_extention(char *map_file)
{
    int i;

    i = 0;
    if (!map_file)
        exit_error("(No file name found)", NULL, NULL);
    while (map_file[i])
        i++;
    if (map_file[i - 5] == '/' || i == 4)
        exit_error("(No file name found)", NULL, NULL);
    if (ft_strncmp(&map_file[i - 4], ".cub", 4) != 0)
        exit_error("(Invalid file extension)", NULL, NULL);
}

void fill_the_file(t_map *map_data, int i, char *map_file)
{
    t_vars vars;

    vars.fd = open(map_file, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor)", map_data, NULL);
    map_data->file = (char **)malloc(sizeof(char *) * (i + 1));
    if (!map_data->file)
        exit_error("(Malloc failed)", map_data, NULL);
    vars.line = get_next_line(vars.fd);
    if (vars.line == NULL)
        exit_error("(empty map !!!)", map_data, NULL);
    vars.i = 0;
    while (vars.line)
    {
        vars.j = 0;
        while (vars.line[vars.j] && vars.line[vars.j] != '\n')
                vars.j++;
        if (vars.j != 0)
            map_data->file[vars.i++] = ft_substr(vars.line, 0, vars.j);
        free(vars.line);
        vars.line = get_next_line(vars.fd);
    }
    map_data->file[vars.i] = NULL;
    vars.i = 0;
    printf("\nhere is the map\n");
    while (map_data->file[vars.i])
    {
        printf("%s\n", map_data->file[vars.i]);
        vars.i++;
    }
    close(vars.fd);
}


void reading_the_file(t_map *map_data, char *map_file)
{
    t_vars vars;

    vars.fd = open(map_file, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor)", map_data, &vars);
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
    fill_the_file(map_data, vars.i, map_file);
}



int define_texture(char **splitted, t_map *map_data)
{
    if (ft_strncmp(splitted[0], "NO", 2) == 0)
    {
        if (map_data->north_txture && (ft_strncmp(map_data->north_txture , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated texture)", map_data, NULL);
        return (map_data->north_txture = ft_strdup(splitted[1]), 1);
    }
    else if (ft_strncmp(splitted[0], "SO", 2) == 0)
    {
        if (map_data->south_txture && (ft_strncmp(map_data->south_txture , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated texture)", map_data, NULL);
        return (map_data->south_txture = ft_strdup(splitted[1]), 1);
    }
    else if (ft_strncmp(splitted[0], "WE", 2) == 0)
    {
        if (map_data->west_txture && (ft_strncmp(map_data->west_txture , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated texture)", map_data, NULL);
        return (map_data->west_txture = ft_strdup(splitted[1]), 1);
    }
    else if (ft_strncmp(splitted[0], "EA", 2) == 0)
    {
        if (map_data->east_txture && (ft_strncmp(map_data->east_txture , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated texture)", map_data, NULL);
        return (map_data->east_txture = ft_strdup(splitted[1]), 1);
    }
    else if (!map_data->north_txture || !map_data->south_txture 
        || !map_data->west_txture || !map_data->east_txture)
        exit_error("(Invalid texture / or no texture found)", map_data, NULL);
    return (2);
}

// here i'm just defining the color without parsing .. I parse later in parsing map_data function...
// void define_colors(char **splitted, t_map *map_data)
// {
//     if (splitted[0][0] == 'F')
//         map_data->floor_color = ft_strdup(splitted[1]);
//     else if (splitted[0][0] == 'C')
//         map_data->ceiling_color = ft_strdup(splitted[1]);
//     // else if (!map_data->ceiling_color || !map_data->floor_color)
//     //     exit_error("(color numbers is missing !!!)");
//     // else
//         return ;
// }


void defining_file_data(t_map *map_data)
{
     t_vars vars;

     vars.x = -1;
     vars.y = -1;
     while (map_data->file[++vars.x])
     {
        if (map_data->file[vars.x][0] == '1' || map_data->file[vars.x][0] == '0')
             exit_error("(Map data is not at the end of the file)", map_data, NULL);
        vars.splitted = ft_split(map_data->file[vars.x], ' ');
        if (define_texture(vars.splitted, map_data) == 2)
            break;
        free(vars.splitted);
     }
     
     printf("\n\n\n----------------------\n\n\n");
        printf("north:%s\n", map_data->north_txture);

}

void parsing_textures(t_map *map_data)
{
    t_vars vars;

    // parsing the textures by try opeining them and check if they are valid
    vars.fd = open(map_data->north_txture, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor north)", map_data, NULL);
    close(vars.fd);
    vars.fd = open(map_data->south_txture, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor)", map_data, NULL);
    close(vars.fd);
    vars.fd = open(map_data->west_txture, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor)", map_data, NULL);
    close(vars.fd);
    vars.fd = open(map_data->east_txture, O_RDONLY);
    if (vars.fd < 0)
        exit_error("(Invalid file descriptor)", map_data, NULL);
    close(vars.fd);
}

void parsing_colors(t_map *map_data)
{
    //pasing the color and convert them into integers
    //using char*(map->floor_color and map->ceiling_color) to int (map->floor and map->ceiling)

    t_vars vars;

    vars.i = 0;
    vars.j = 0;
    vars.k = 0;
    vars.l = 0;
    vars.m = 0;
    vars.n = 0;
    while (map_data->floor_color[vars.i])
    {
        if (map_data->floor_color[vars.i] >= '0' && map_data->floor_color[vars.i] <= '9')
        {
            vars.j = vars.j * 10 + (map_data->floor_color[vars.i] - '0');
            vars.k = 1;
        }
        else if (map_data->floor_color[vars.i] == ',')
        {
            vars.l = vars.j;
            vars.j = 0;
        }
        else
            exit_error("(Invalid color number)", map_data, NULL);
        vars.i++;
    }
    // ceiling 
    vars.i = 0;
    while (map_data->ceiling_color[vars.i])
    {
        if (map_data->ceiling_color[vars.i] >= '0' && map_data->ceiling_color[vars.i] <= '9')
        {
            vars.m = vars.m * 10 + (map_data->ceiling_color[vars.i] - '0');
            vars.n = 1;
        }
        else if (map_data->ceiling_color[vars.i] == ',')
        {
            vars.n = vars.m;
            vars.m = 0;
        }
        else
            exit_error("(Invalid color number)", map_data, NULL);
        vars.i++;
    }

    // printing the color now 
    printf("\n\n\n----------------------\n\n\n");
    printf("floor color: %d, %d, %d\n", vars.l, vars.j, vars.k);
    printf("ceiling color: %d, %d, %d\n", vars.n, vars.m, vars.k);
    printf("\n\n\n----------------------\n\n\n");

    
}


void parsing_file_data(t_map *map_data)
{
    parsing_textures(map_data);
    // parsing the colors by converting them to numbers
    parsing_colors(map_data);
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
    defining_file_data(&map);
    parsing_file_data(&map);
    // extract_map(&map);
    // parsing_map(&map);
    // execution(&map);
    
    // while(1)
    // {
        printf("PERFECTOO😘\n");
    // }
    

    return 0;
}