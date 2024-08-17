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
    double i;
    double r;

    pixel = data->pixel;
    i = 60;
    data->rx = data->px + pixel / 6;
    data->ry = data->py + pixel / 6;
    r = i / WIDTH;
    data->r_angle = data->angle + 30;
    while (i > 0)
    {
        data->r_angle -= r;
        y = data->ry;
        x = data->rx;
        while(y >= 0 && y < data->height && x >= 0 && x < data->width
            && data->map_s->map[(int)(y / data->pixel)][(int)(x / data->pixel)]
            && data->map_s->map[(int)(y / data->pixel)][(int)(x / data->pixel)] != '1')
        {
            my_mlx_pixel_put(data, x, y, 0xb9fba5, 0);
            x += cos(d_to_r(data->r_angle));
            y -= sin(d_to_r(data->r_angle));
        }
        i -= r;
    }
}
