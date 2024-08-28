#include "Cub3d.h"

bool ft_check_collision(t_data *data, int x, int y, int direction)
{
    int pixel;
    int speed;

    pixel = data->pixel;
    speed = data->speed;

    // printf("x: %f, y: %f\n", (y + (sin(d_to_r(data->angle)) * speed)) / pixel, (x - (cos(d_to_r(data->angle)) * speed)) / pixel);
    if (direction == 1)
    {
        if (data->map_s->map[(int)(y - (sin(d_to_r(data->angle)) * speed)) / pixel][(int)(x + (cos(d_to_r(data->angle)) * speed)) / pixel]
            && data->map_s->map[(int)(y - (sin(d_to_r(data->angle)) * speed)) / pixel][(int)(x + (cos(d_to_r(data->angle)) * speed)) / pixel] != '1')
            return true;
    }
    else if (direction == 2)
    {
        if (data->map_s->map[(int)(y + (sin(d_to_r(data->angle)) * speed)) / pixel][(int)(x - (cos(d_to_r(data->angle)) * speed)) / pixel]
            && data->map_s->map[(int)(y + (sin(d_to_r(data->angle)) * speed)) / pixel][(int)(x - (cos(d_to_r(data->angle)) * speed)) / pixel] != '1')
            return true;
    }
    return false;
}

static int ft_up(t_data *data)
{
    // printf("x: %d, y: %d, angle: %d\n", data->px, data->py, data->angle);
    if ((data->ry - sin(d_to_r(data->angle)) * data->speed) >= 0
        && (data->rx + cos(d_to_r(data->angle)) * data->speed) <= data->width
    && ft_check_collision(data, data->rx, data->ry, 1))
    {
        // printf("2. x: %f, y: %d, angle: %d\n", (cos(d_to_r(data->angle)) * data->speed), data->py, data->angle);
        data->px += (int)(cos(d_to_r(data->angle)) * data->speed);
        data->py -= (int)(sin(d_to_r(data->angle)) * data->speed);
    }
    return 0;
}

static int ft_down(t_data *data)
{
    // printf("x: %d, y: %d, angle: %d\n", data->px, data->py, data->angle);
    if ((data->ry + sin(d_to_r(data->angle)) * data->speed) <= data->height
        && (data->rx - cos(d_to_r(data->angle)) * data->speed) >= 0
        && ft_check_collision(data, data->rx, data->ry, 2))
    {
        data->px -= (int)(cos(d_to_r(data->angle)) * data->speed);
        data->py += (int)(sin(d_to_r(data->angle)) * data->speed);
    }
    // printf("2. x: %d, y: %d, angle: %d\n", data->px, data->py, data->angle);
    return 0;
}

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == ESC)
        ft_quit_game(data);
    if (keycode == D)
    {
        data->angle -= 0.9;
        if (data->angle <= 0)
            data->angle += 360;
    }
    if (keycode == A)
    {
        data->angle += 0.9;
        if (data->angle >= 360)
            data->angle -= 360;
    }
    if (keycode == W)
        return (ft_up(data));
    if (keycode == S)
        return (ft_down(data));
    return 0;
}