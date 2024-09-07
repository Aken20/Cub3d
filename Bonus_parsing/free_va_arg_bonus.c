# include "../Cub3d_bonus.h"



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
            if (*ptr)
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
