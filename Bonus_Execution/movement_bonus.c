# include "../Cub3d_bonus.h"

// bool ft_check_collision(t_data *data, int move_x, int move_y)
// {
//     if (move_y >= 0 && move_x >= 0 && move_y < data->map->height && move_x < (int)ft_strlen(data->map->map[move_y])
//         && data->map->map[move_y][move_x] && data->map->map[move_y][move_x] != '1')
//         return true;
//     return false;
// }

static int ft_up(t_data *data)
{
    int speed;
    int pixel;
    int move_x;
    int move_y;

    speed = data->map->speed;
    pixel = data->map->pixel;
    move_x = (data->map->rx + cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    move_y = (data->map->ry - sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
            && move_x < (int)ft_strlen(data->map->map[move_y]) && data->map->map[move_y][move_x]
            && data->map->map[move_y][move_x] != '1' && speed--)
    {
        data->map->px += cos(d_to_r(data->map->angle));
        data->map->rx += cos(d_to_r(data->map->angle));
        data->map->py -= sin(d_to_r(data->map->angle));
        data->map->ry -= sin(d_to_r(data->map->angle));
        move_x = (data->map->rx + cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
        move_y = (data->map->ry - sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    }
    return 0;
}

static int ft_down(t_data *data)
{
    int speed;
    int pixel;
    int move_x;
    int move_y;

    speed = data->map->speed;
    pixel = data->map->pixel;
    move_x = (data->map->rx - cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    move_y = (data->map->ry + sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
            && move_x < (int)ft_strlen(data->map->map[move_y]) && data->map->map[move_y][move_x]
            && data->map->map[move_y][move_x] != '1' && speed--)
    {
        data->map->px -= cos(d_to_r(data->map->angle));
        data->map->rx -= cos(d_to_r(data->map->angle));
        data->map->py += sin(d_to_r(data->map->angle));
        data->map->ry += sin(d_to_r(data->map->angle));
        move_x = (data->map->rx - cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
        move_y = (data->map->ry + sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    }
    return 0;
}

static int ft_left(t_data *data)
{
    int speed;
    int pixel;
    int move_x;
    int move_y;

    speed = data->map->speed;
    pixel = data->map->pixel;
    move_x = (data->map->rx - sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    move_y = (data->map->ry - cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
            && move_x < (int)ft_strlen(data->map->map[move_y]) && data->map->map[move_y][move_x]
            && data->map->map[move_y][move_x] != '1' && speed--)
    {
        data->map->px -= sin(d_to_r(data->map->angle));
        data->map->rx -= sin(d_to_r(data->map->angle));
        data->map->py -= cos(d_to_r(data->map->angle));
        data->map->ry -= cos(d_to_r(data->map->angle));
        move_x = (data->map->rx - sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
        move_y = (data->map->ry - cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    }
    return 0;
}

static int ft_right(t_data *data)
{
    int speed;
    int pixel;
    int move_x;
    int move_y;

    speed = data->map->speed;
    pixel = data->map->pixel;
    move_x = (data->map->rx + sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    move_y = (data->map->ry + cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
            && move_x < (int)ft_strlen(data->map->map[move_y]) && data->map->map[move_y][move_x]
            && data->map->map[move_y][move_x] != '1' && speed--)
    {
        data->map->px += sin(d_to_r(data->map->angle));
        data->map->rx += sin(d_to_r(data->map->angle));
        data->map->py += cos(d_to_r(data->map->angle));
        data->map->ry += cos(d_to_r(data->map->angle));
        move_x = (data->map->rx + sin(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
        move_y = (data->map->ry + cos(d_to_r(data->map->angle)) * (pixel / 1.5)) / pixel;
    }
    return 0;
}

int ft_mouse_hocks(int x, int y, t_data *data)
{
    static int previous_x;

    if (x > previous_x)
    {
        previous_x = x;
        data->map->angle -= ((y * 0) + 3);
        if (data->map->angle < 0)
            data->map->angle += 360;
    }
    else
    {
        previous_x = x;
        data->map->angle += 3;
        if (data->map->angle > 360)
            data->map->angle -= 360;
    }
    if (x == ESC)
        ft_quit_game(data);
    return (0);
}

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == ESC)
        ft_quit_game(data);
    if (keycode == RA)
    {
        data->map->angle -= 3;
        if (data->map->angle < 0)
            data->map->angle += 360;
    }
    if (keycode == LA)
    {
        data->map->angle += 3;
        if (data->map->angle > 360)
            data->map->angle -= 360;
    }
    if (keycode == A)
        ft_left(data);
    if (keycode == D)
        ft_right(data);
    if (keycode == W)
        ft_up(data);
    if (keycode == S)
        ft_down(data);
    // ft_render(data);
    return 0;
}