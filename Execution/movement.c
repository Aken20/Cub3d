#include "../Cub3d.h"

bool ft_check_collision(t_data *data, int x, int y, int direction)
{
    int pixel;
    int speed;
    int move_x;
    int move_y;

    pixel = data->map->pixel;
    speed = data->map->speed;

    if (direction == 1)
    {
        if (cos(d_to_r(data->map->angle)) > 0)
            move_x = (x + (pixel / 6) + cos(d_to_r(data->map->angle)) * speed) / pixel;
        else
            move_x = (x - (pixel / 6) + cos(d_to_r(data->map->angle)) * speed) / pixel;
        if (sin(d_to_r(data->map->angle)) > 0)
            move_y = (y - (pixel / 6) - sin(d_to_r(data->map->angle)) * speed) / pixel;
        else
            move_y = (y + (pixel / 6) - sin(d_to_r(data->map->angle)) * speed) / pixel;
        printf("x: %d, y: %d\n", move_x, move_y);
        if (move_y >= 0 && move_x >= 0 && move_y < data->map->height && move_x < (int)ft_strlen(data->map->map[move_y])
            && data->map->map[move_y][move_x] && data->map->map[move_y][move_x] != '1')
            return true;
    }
    else if (direction == 2)
    {
        if (cos(d_to_r(data->map->angle)) > 0)
            move_x = (x - (pixel / 6) - cos(d_to_r(data->map->angle)) * speed) / pixel;
        else
            move_x = (x + (pixel / 6) - cos(d_to_r(data->map->angle)) * speed) / pixel;
        if (sin(d_to_r(data->map->angle)) > 0)
            move_y = (y + (pixel / 6) + sin(d_to_r(data->map->angle)) * speed) / pixel;
        else
            move_y = (y - (pixel / 6) + sin(d_to_r(data->map->angle)) * speed) / pixel;
        printf("x: %d, y: %d\n", move_x, move_y);
        if (move_y >= 0 && move_x >= 0 && move_y < data->map->height && move_x < (int)ft_strlen(data->map->map[move_y])
            && data->map->map[move_y][move_x] && data->map->map[move_y][move_x] != '1')
            return true;
    }
    return false;
}

static int ft_up(t_data *data)
{
    // printf("x: %d, y: %d, angle: %d\n", data->map->px, data->map->py, data->map->angle);
    if ((data->map->ry - (int)sin(d_to_r(data->map->angle)) * data->map->speed) > 0
        && (data->map->rx + (int)cos(d_to_r(data->map->angle)) * data->map->speed) < data->width
    && ft_check_collision(data, data->map->rx, data->map->ry, 1))
    {
        // printf("x: %f, y: %f, angle: %f\n", (int)(cos(d_to_r(data->map->angle)) * data->map->speed), (sin(d_to_r(data->map->angle)) * data->map->speed), data->map->angle);
        data->map->px += (int)(cos(d_to_r(data->map->angle)) * data->map->speed);
        data->map->py -= (int)(sin(d_to_r(data->map->angle)) * data->map->speed);
    }
    return 0;
}

static int ft_down(t_data *data)
{
    // printf("x: %d, y: %d, angle: %d\n", data->map->px, data->map->py, data->map->angle);
    if ((data->map->ry + sin(d_to_r(data->map->angle)) * data->map->speed) < data->height
        && (data->map->rx - cos(d_to_r(data->map->angle)) * data->map->speed) > 0
        && ft_check_collision(data, data->map->rx, data->map->ry, 2))
    {
        data->map->px -= (int)(cos(d_to_r(data->map->angle)) * data->map->speed);
        data->map->py += (int)(sin(d_to_r(data->map->angle)) * data->map->speed);
    }
    // printf("2. x: %d, y: %d, angle: %d\n", data->map->px, data->map->py, data->map->angle);
    return 0;
}

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == ESC)
        ft_quit_game(data);
    if (keycode == D)
    {
        data->map->angle -= 3;
        if (data->map->angle < 0)
            data->map->angle += 360;
        ft_render(data);
    }
    if (keycode == A)
    {
        data->map->angle += 3;
        if (data->map->angle > 360)
            data->map->angle -= 360;
        ft_render(data);
    }
    if (keycode == W)
        return (ft_up(data), ft_render(data));
    if (keycode == S)
        return (ft_down(data), ft_render(data));
    return 0;
}