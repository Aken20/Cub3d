#include "../Cub3d.h"

bool ft_check_collision(t_data *data, int x, int y, int direction)
{
    int pixel;
    int speed;
    int move_x;
    int move_y;

    pixel = data->map_s->pixel;
    speed = data->map_s->speed;

    if (direction == 1)
    {
        if (cos(d_to_r(data->map_s->angle)) > 0)
            move_x = (x + (pixel / 6) + cos(d_to_r(data->map_s->angle)) * speed) / pixel;
        else
            move_x = (x - (pixel / 6) + cos(d_to_r(data->map_s->angle)) * speed) / pixel;
        if (sin(d_to_r(data->map_s->angle)) > 0)
            move_y = (y - (pixel / 6) - sin(d_to_r(data->map_s->angle)) * speed) / pixel;
        else
            move_y = (y + (pixel / 6) - sin(d_to_r(data->map_s->angle)) * speed) / pixel;
        printf("x: %d, y: %d\n", move_x, move_y);
        if (move_y >= 0 && move_x >= 0 && move_y < data->map_s->height && move_x < (int)ft_strlen(data->map_s->map[move_y])
            && data->map_s->map[move_y][move_x] && data->map_s->map[move_y][move_x] != '1')
            return true;
    }
    else if (direction == 2)
    {
        if (cos(d_to_r(data->map_s->angle)) > 0)
            move_x = (x - (pixel / 6) - cos(d_to_r(data->map_s->angle)) * speed) / pixel;
        else
            move_x = (x + (pixel / 6) - cos(d_to_r(data->map_s->angle)) * speed) / pixel;
        if (sin(d_to_r(data->map_s->angle)) > 0)
            move_y = (y + (pixel / 6) + sin(d_to_r(data->map_s->angle)) * speed) / pixel;
        else
            move_y = (y - (pixel / 6) + sin(d_to_r(data->map_s->angle)) * speed) / pixel;
        printf("x: %d, y: %d\n", move_x, move_y);
        if (move_y >= 0 && move_x >= 0 && move_y < data->map_s->height && move_x < (int)ft_strlen(data->map_s->map[move_y])
            && data->map_s->map[move_y][move_x] && data->map_s->map[move_y][move_x] != '1')
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