#include "Cub3d.h"

bool ft_check_collision(t_data *data, int x, int y, int direction)
{
    int pixel;
    int speed;

    pixel = data->map_s->pixel;
    speed = data->map_s->speed;

    // printf("x: %f, y: %f\n", (y + (sin(d_to_r(data->map_s->angle)) * speed)) / pixel, (x - (cos(d_to_r(data->map_s->angle)) * speed)) / pixel);
    if (direction == 1)
    {
        if (data->map_s->map[(int)(y - ((int)sin(d_to_r(data->map_s->angle) * speed))) / pixel][(int)(x + ((int)cos(d_to_r(data->map_s->angle) * speed))) / pixel]
            && data->map_s->map[(int)(y - ((int)sin(d_to_r(data->map_s->angle) * speed))) / pixel][(int)(x + ((int)cos(d_to_r(data->map_s->angle) * speed))) / pixel] != '1')
            return true;
    }
    else if (direction == 2)
    {
        if (data->map_s->map[(int)(y + ((int)sin(d_to_r(data->map_s->angle) * speed))) / pixel][(int)(x - ((int)cos(d_to_r(data->map_s->angle) * speed))) / pixel]
            && data->map_s->map[(int)(y + ((int)sin(d_to_r(data->map_s->angle) * speed))) / pixel][(int)(x - ((int)cos(d_to_r(data->map_s->angle) * speed))) / pixel] != '1')
            return true;
    }
    return false;
}

static int ft_up(t_data *data)
{
    // printf("x: %d, y: %d, angle: %d\n", data->map_s->px, data->map_s->py, data->map_s->angle);
    if ((data->map_s->ry - (int)sin(d_to_r(data->map_s->angle)) * data->map_s->speed) > 0
        && (data->map_s->rx + (int)cos(d_to_r(data->map_s->angle)) * data->map_s->speed) < data->width
    && ft_check_collision(data, data->map_s->rx, data->map_s->ry, 1))
    {
        // printf("x: %f, y: %f, angle: %f\n", (int)(cos(d_to_r(data->map_s->angle)) * data->map_s->speed), (sin(d_to_r(data->map_s->angle)) * data->map_s->speed), data->map_s->angle);
        data->map_s->px += (int)(cos(d_to_r(data->map_s->angle)) * data->map_s->speed);
        data->map_s->py -= (int)(sin(d_to_r(data->map_s->angle)) * data->map_s->speed);
    }
    return 0;
}

static int ft_down(t_data *data)
{
    // printf("x: %d, y: %d, angle: %d\n", data->map_s->px, data->map_s->py, data->map_s->angle);
    if ((data->map_s->ry + sin(d_to_r(data->map_s->angle)) * data->map_s->speed) < data->height
        && (data->map_s->rx - cos(d_to_r(data->map_s->angle)) * data->map_s->speed) > 0
        && ft_check_collision(data, data->map_s->rx, data->map_s->ry, 2))
    {
        data->map_s->px -= (int)(cos(d_to_r(data->map_s->angle)) * data->map_s->speed);
        data->map_s->py += (int)(sin(d_to_r(data->map_s->angle)) * data->map_s->speed);
    }
    // printf("2. x: %d, y: %d, angle: %d\n", data->map_s->px, data->map_s->py, data->map_s->angle);
    return 0;
}

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == ESC)
        ft_quit_game(data);
    if (keycode == D)
    {
        data->map_s->angle--;
        if (data->map_s->angle < 0)
            data->map_s->angle += 360;
    }
    if (keycode == A)
    {
        data->map_s->angle++;
        if (data->map_s->angle > 360)
            data->map_s->angle -= 360;
    }
    if (keycode == W)
        return (ft_up(data));
    if (keycode == S)
        return (ft_down(data));
    return 0;
}