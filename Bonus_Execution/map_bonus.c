# include "../Cub3d_bonus.h"

void    get_width(t_data *data)
{
    int i;

    i = 0;
    while (data->map->map[i])
    {
        if (data->map->width < (int)ft_strlen(data->map->map[i]))
            data->map->width = (int)ft_strlen(data->map->map[i]);
        i++;
    }
}

void ft_player_find(t_data *data)
{
    int i;
    int j;
    char c;

    i = -1;
    while (data->map->map[++i])
    {
        j = -1;
        while (data->map->map[i][++j])
            if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S'
                || data->map->map[i][j] == 'W' || data->map->map[i][j] == 'E')
            {
                data->map->px = (j * data->map->pixel) + (data->map->pixel / 3);
                data->map->py = (i * data->map->pixel) + (data->map->pixel / 3);
                c = data->map->map[i][j];
                if (c == 'N')
                    data->map->angle = 90;
                else if (c == 'W')
                    data->map->angle = 180;
                else if (c == 'S')
                    data->map->angle = 270;
                else if (c == 'E')
                    data->map->angle = 0;
            }
    }
}
