#include "Cub3d.h"

float d_to_r(int degree)
{
    return (degree * (PI / 180));
}

void draw_ray_screen(t_data *data, float length, int x)
{
    float y;

    // if (length > HEIGHT)
    //     length = 0;
    // else
    // length = (HEIGHT / data->height);
    length = HEIGHT - (length * (HEIGHT / data->height));
    printf("length: %f\n", length);
    if (length < 0)
        length = 0;
    y = (HEIGHT / 2) - (length / 2);
    while(length >= 0)
    {
        length--;
        my_mlx_pixel_put(data, x, y + length, 0xb9fba5, 1);
    }

}

void draw_ray(t_data *data)
{
    float y;
    float x;
    float length;
    double fov;
    int k = 0;
    double r;

    fov = 90;
    data->rx = data->px + data->pixel / 6;
    data->ry = data->py + data->pixel / 6;
    r = fov / WIDTH;
    data->r_angle = data->angle + fov / 2;
    while (fov > 0)
    {
        data->r_angle -= r;
        y = data->ry;
        x = data->rx;
        length = 0;
        // if (data->r_angle >= 180)
            while(y >= 0 && y <= data->height && x >= 0 && x <= data->width
                && data->map_s->map[(int)(y) / data->pixel][(int)(x) / data->pixel]
                && data->map_s->map[(int)(y) / data->pixel][(int)(x) / data->pixel] != '1')
            {
                length += 0.5;
                my_mlx_pixel_put(data, x, y, 0xb9fba5, 0);
                x += cos(d_to_r(data->r_angle));
                y -= sin(d_to_r(data->r_angle));
            }
        // else
        //     while(y >= 0 && y <= data->height && x >= 0 && x <= data->width
        //         && data->map_s->map[(int)(y) / data->pixel][(int)(x) / data->pixel]
        //         && data->map_s->map[(int)(y) / data->pixel][(int)(x) / data->pixel] != '1')
        //     {
        //         length++;
        //         my_mlx_pixel_put(data, x, y, 0xb9fba5, 0);
        //         x -= cos(d_to_r(data->r_angle));
        //         y += sin(d_to_r(data->r_angle));
        //     }
        length *= cos(d_to_r(data->angle - data->r_angle));
        draw_ray_screen(data, length, k++);
        fov -= r;
    }
}
