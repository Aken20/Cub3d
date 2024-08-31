#include "Cub3d.h"


int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
    printf("hena ----------------------------------------\n");
    free_all(2, &vars->line, &vars->tmp);
    printf("hena ----------------------------------------\n");
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
            exit_error("(Found duplicated texture NO)", map_data, NULL);
        return (map_data->north_txture = ft_strdup(splitted[1]), 1);
    }
    else if (ft_strncmp(splitted[0], "SO", 2) == 0)
    {
        if (map_data->south_txture && (ft_strncmp(map_data->south_txture , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated texture SO)", map_data, NULL);
        return (map_data->south_txture = ft_strdup(splitted[1]), 1);
    }
    else if (ft_strncmp(splitted[0], "WE", 2) == 0)
    {
        if (map_data->west_txture && (ft_strncmp(map_data->west_txture , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated texture WE)", map_data, NULL);
        return (map_data->west_txture = ft_strdup(splitted[1]), 1);
    }
    else if (ft_strncmp(splitted[0], "EA", 2) == 0)
    {
        if (map_data->east_txture && (ft_strncmp(map_data->east_txture , splitted[1], ft_strlen(splitted[1])) == 0))
            exit_error("(Found duplicated texture EA)", map_data, NULL);
        return (map_data->east_txture = ft_strdup(splitted[1]), 1);
    }
    return (4);
}

void defining_textures(t_map *map_data)
{
     t_vars vars;

     vars.x = -1;
     vars.y = -1;
     int txturecounter = 0;
     while (map_data->file[++vars.x] && txturecounter != 4)
     {
        if (map_data->file[vars.x][0] == '1' || map_data->file[vars.x][0] == '0')
             exit_error("(Map data is not at the end of the file)", map_data, NULL);
        vars.splitted = ft_split(map_data->file[vars.x], ' ');
        if (ft_strcmp(vars.splitted[0], "NO") == 0 || ft_strcmp(vars.splitted[0], "SO") == 0
            || ft_strcmp(vars.splitted[0], "WE") == 0 || ft_strcmp(vars.splitted[0], "EA") == 0)
        {
            txturecounter += define_texture(vars.splitted, map_data);
            free(vars.splitted);
        } else if (!ft_strncmp(vars.splitted[0], "C", 1) || !ft_strncmp(vars.splitted[0], "F", 1))
            exit_error("(Undefined character(s))", map_data, NULL);
     }
    if (txturecounter != 4)
        exit_error("(Invalid texture or no texture found)", map_data, NULL);
     
    printf("\n\n\n----------------------\n\n\n");
    printf("north:%s\n", map_data->north_txture);

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

void defining_colors(t_map *map_data)
{
    t_vars vars;

    vars.x = -1;
    vars.y = -1;
    int iscolorfound = 0;
    while (map_data->file[++vars.x] && iscolorfound != 2)
    {
        if ((map_data->file[vars.x][0] == 'C' || map_data->file[vars.x][0] == 'F') && map_data->file[vars.x][1] == ' ')
        {
            vars.splitted = ft_split(map_data->file[vars.x], ' ');
            iscolorfound += define_colors(vars.splitted, map_data);
            free(vars.splitted);
        }
        else if ((map_data->file[vars.x][0] == '1' || map_data->file[vars.x][0] == '0'))
                exit_error("(Invalid color or no color found)", map_data, NULL);
    }
    if (iscolorfound != 2)
        exit_error("(Invalid color or no color found)", map_data, NULL);
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



void parsing_testures(t_map *map_data)
{
    parsing_textures(map_data);
    // parsing the colors by converting them to numbers
    // parsing_colors(map_data);
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
    printf("height:%d\n", map_data->height);
    
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
            printf("y:%d, map->file[vars.x]:%s\n", vars.y, map_data->file[vars.x]);
            map_data->map[vars.y] = ft_strdup(map_data->file[vars.x]);
        }
    }
    map_data->map[vars.y + 1] = NULL;
    
}





void parsing_the_map(t_map *map_data)
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
                // printf("y:%d x:%d\n", vars.y, vars.x);
                // printf("map_data[vars.y - 1][vars.x]:%c\n", map_data->map[vars.y - 1][vars.x]);
                if (vars.y == 0 || vars.x == 0)
                    exit_error("(Invalid map)", map_data, NULL);
                if ((map_data->map[vars.y - 1][vars.x] != '1' && map_data->map[vars.y - 1][vars.x] != '0') 
                    || (map_data->map[vars.y + 1][vars.x] != '1' && map_data->map[vars.y + 1][vars.x] != '0')
                    || (map_data->map[vars.y][vars.x - 1] != '1' && map_data->map[vars.y][vars.x - 1] != '0')
                    || (map_data->map[vars.y][vars.x + 1] != '1' && map_data->map[vars.y][vars.x + 1] != '0'))
                    exit_error("(Invalid map)", map_data, NULL);
            }
        }
    }
}

void convert_white_spaces(t_map *map_data)
{
    t_vars vars;

    vars.x = -1;
    vars.y = -1;
    while (map_data->file[++vars.y])
    {
        vars.x = -1;
        while (map_data->file[vars.y][++vars.x])
        {
            if (map_data->file[vars.y][vars.x] >= 9 && map_data->file[vars.y][vars.x] <= 13)
                map_data->file[vars.y][vars.x] = ' ';
        }
    }
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
    convert_white_spaces(&map);
    defining_textures(&map);
    defining_colors(&map);
    // parsing_testures(&map);
    extracting_the_map(&map);
    parsing_the_map(&map);
    // parsing_colors(&map);
    // extract_map(&map);
    // parsing_map(&map);
    // execution(&map);
    
    // while(1)
    // {
        printf("PERFECTOO😘\n");
    // }
    

    return 0;
}