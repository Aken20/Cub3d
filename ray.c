#include "Cub3d.h"

float d_to_r(int degree)
{
    return (degree * (PI / 180));
}

void draw_ray(t_data *data)
{
    float y;
    float x;
    int pixel;

    pixel = data->pixel / 3;
    data->rx = data->px + pixel / 2;
    data->ry = data->py + pixel / 2;
    y = data->ry;
    x = data->rx;

    // data->angle = 90;
    while (pixel > 0)
    {
        my_mlx_pixel_put(data, x, y, 0x000000);
        x += cos(d_to_r(data->angle));
        y -= sin(d_to_r(data->angle));
        pixel--;
    }
}