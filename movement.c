#include "Cub3d.h"

bool ft_check_collision(t_data *data, int x, int y, int direction)
{
    int pixel;
    int p_size;
    int speed;

    pixel = data->pixel;
    speed = data->speed;
    p_size = pixel / 3 - 1;

    // printf("x: %d, y: %d\n", x / pixel, y / pixel);
    if (direction == 1)
    {
        if (data->map_s->map[(int)(x + (cos(d_to_r(data->angle)) * data->speed)) / pixel][(int)(y - (sin(d_to_r(data->angle)) * data->speed)) / pixel] != '1')
            return true;
    }
    else if (direction == 2)
    {
        if (data->map_s->map[(int)(x - (cos(d_to_r(data->angle)) * data->speed)) / pixel][(int)(y + (sin(d_to_r(data->angle)) * data->speed)) / pixel] != '1')
            return true;
    }
    return false;
}

static int ft_up(t_data *data)
{
    if ((data->py - sin(d_to_r(data->angle)) * data->speed) > 0 && ft_check_collision(data, data->px, data->py, 1))
    {
        // printf("x: %d, y: %d\n", data->px, data->py);
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->px += cos(d_to_r(data->angle)) * data->speed;
        data->py -= sin(d_to_r(data->angle)) * data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    
    return 0;
}

static int ft_down(t_data *data)
{
    if (data->py <= data->height && ft_check_collision(data, data->px, data->py, 2))
    {
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->px -= cos(d_to_r(data->angle)) * data->speed;
        data->py += sin(d_to_r(data->angle)) * data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    return 0;
}

// static int ft_left(t_data *data)
// {
//     if (data->px - data->speed > 0 && ft_check_collision(data, data->px, data->py, 3))
//     {
//         data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
//         data->px -= data->speed;
//         data->rx -= data->speed;
//         data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
//     }
//     return 0;
// }

// static int ft_right(t_data *data)
// {
//     if (data->px <= data->width && ft_check_collision(data, data->px, data->py, 4))
//     {
//         data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
//         data->px += data->speed;
//         data->rx += data->speed;
//         data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
//     }
//     return 0;
// }

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == ESC)
        ft_quit_game(data);
    if (keycode == RA)
        data->angle -= 3;
    if (keycode == LA)
        data->angle += 3;
    if (keycode == W)
        return (ft_up(data));
    if (keycode == S)
        return (ft_down(data));
    // if (keycode == A)
    //     return (ft_left(data));
    // if (keycode == D)
    //     return (ft_right(data));
    return 0;
}