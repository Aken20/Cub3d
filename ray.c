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
    int i;

    pixel = data->pixel;
    i = 60;
    data->rx = data->px + pixel / 6;
    data->ry = data->py + pixel / 6;

    data->r_angle = data->angle + 30;
    while (i > 0)
    {
        data->r_angle--;
        y = data->ry;
        x = data->rx;
        // if (data->r_angle <= 180)
            while(y >= 0 && data->map_s->map[(int)(y / data->pixel)][(int)(x / data->pixel)] != '1')
            {
                my_mlx_pixel_put(data, x, y, 0xb9fba5);
                x += cos(d_to_r(data->r_angle));
                y -= sin(d_to_r(data->r_angle));
            }
        // else
        //     while(y <= data->height && data->map_s->map[(int)(y / data->pixel)][(int)(x / data->pixel)] != '1')
        //     {
        //         my_mlx_pixel_put(data, x, y, 0x000000);
        //         x -= cos(d_to_r(data->r_angle));
        //         y += sin(d_to_r(data->r_angle));
        //     }
        i--;
    }
}