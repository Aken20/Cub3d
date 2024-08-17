#include "Cub3d.h"

bool ft_check_collision(t_data *data, int x, int y, int direction)
{
    int pixel;
    // int p_size;
    int speed;

    pixel = data->pixel;
    speed = data->speed;
    // p_size = pixel / 3 - 1;

    printf("x: %f, y: %f\n", (y + (sin(d_to_r(data->angle)) * speed)) / pixel, (x - (cos(d_to_r(data->angle)) * speed)) / pixel);
    if (direction == 1)
    {
        if (data->map_s->map[(int)(y - (sin(d_to_r(data->angle)) * speed)) / pixel][(int)(x + (cos(d_to_r(data->angle)) * speed)) / pixel] != '1')
            return true;
    }
    else if (direction == 2)
    {
        if (data->map_s->map[(int)(y + (sin(d_to_r(data->angle)) * speed)) / pixel][(int)(x - (cos(d_to_r(data->angle)) * speed)) / pixel] != '1')
            return true;
    }
    return false;
}

static int ft_up(t_data *data)
{
    printf("x: %f, y: %f, angle: %d\n", (cos(d_to_r(data->angle)) * data->speed), (sin(d_to_r(data->angle)) * data->speed), data->angle);
    if ((data->ry - sin(d_to_r(data->angle)) * data->speed) >= 0
        && (data->rx + cos(d_to_r(data->angle)) * data->speed) <= data->width
    && ft_check_collision(data, data->rx, data->ry, 1))
    {
        data->px += (cos(d_to_r(data->angle)) * data->speed);
        data->py -= (sin(d_to_r(data->angle)) * data->speed);
    }
    return 0;
}

static int ft_down(t_data *data)
{
    printf("x: %f, y: %f, angle: %d\n", (cos(d_to_r(data->angle)) * data->speed), (sin(d_to_r(data->angle)) * data->speed), data->angle);
    if ((data->ry + sin(d_to_r(data->angle)) * data->speed) <= data->height
        && (data->rx - cos(d_to_r(data->angle)) * data->speed) >= 0
        && ft_check_collision(data, data->rx, data->ry, 2))
    {
        data->px -= (cos(d_to_r(data->angle)) * data->speed);
        data->py += (sin(d_to_r(data->angle)) * data->speed);
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
        data->angle += 3;
    if (keycode == LA)
        data->angle -= 3;
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