#include "../Cub3d.h"

void    get_width(t_data *data)
{
    int i;

    i = 0;
    while (data->map_s->map[i])
    {
        if (data->map_s->width < (int)ft_strlen(data->map_s->map[i]))
            data->map_s->width = (int)ft_strlen(data->map_s->map[i]);
        i++;
    }
}

void ft_player_find(t_data *data)
{
    int i;
    int j;
    char c;

    i = -1;
    while (data->map_s->map[++i])
    {
        j = -1;
        while (data->map_s->map[i][++j])
            if (data->map_s->map[i][j] == 'N' || data->map_s->map[i][j] == 'S'
                || data->map_s->map[i][j] == 'W' || data->map_s->map[i][j] == 'E')
            {
                data->map_s->px = (j * data->map_s->pixel) + (data->map_s->pixel / 3);
                data->map_s->py = (i * data->map_s->pixel) + (data->map_s->pixel / 3);
                c = data->map_s->map[i][j];
                if (c == 'N')
                    data->map_s->angle = 90;
                else if (c == 'W')
                    data->map_s->angle = 180;
                else if (c == 'S')
                    data->map_s->angle = 270;
                else if (c == 'E')
                    data->map_s->angle = 0;
            }
    }
}
