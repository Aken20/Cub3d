#include "Cub3d.h"

static int ft_up(t_data *data)
{
    if (data->py - data->speed > 0 && ft_check_collision(data, data->px, data->py, 1))
    {
        // printf("x: %d, y: %d\n", data->px, data->py);
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->py -= data->speed;
        data->ry -= data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    
    return 0;
}

static int ft_down(t_data *data)
{
    if (data->py <= data->height && ft_check_collision(data, data->px, data->py, 2))
    {
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->py += data->speed;
        data->ry += data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    return 0;
}

static int ft_left(t_data *data)
{
    if (data->px - data->speed > 0 && ft_check_collision(data, data->px, data->py, 3))
    {
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->px -= data->speed;
        data->rx -= data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    return 0;
}

static int ft_right(t_data *data)
{
    if (data->px <= data->width && ft_check_collision(data, data->px, data->py, 4))
    {
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->px += data->speed;
        data->rx += data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    return 0;
}

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == ESC)
        ft_quit_game(data);
    if (keycode == W)
        return (ft_up(data));
    if (keycode == S)
        return (ft_down(data));
    if (keycode == A)
        return (ft_left(data));
    if (keycode == D)
        return (ft_right(data));
    return 0;
}