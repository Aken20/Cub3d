#include "Cub3d.h"

float d_to_r(int degree)
{
    return (degree * (PI / 180));
}

void draw_ray_screen(t_data *data, int length, int x)
{
    int y;

    // if (length > HEIGHT)
    //     length = 0;
    // else
    length *= (HEIGHT / data->height);
    length = HEIGHT - length;
    printf("length: %d\n", length);
    if (length < 0)
        length *= -1;
    y = (HEIGHT / 2) - (length / 2);
    while(length >= 0)
    {
        length--;
        my_mlx_pixel_put(data, x, y++, 0xb9fba5, 1);
    }

}

void draw_ray(t_data *data)
{
    float y;
    float x;
    float length;
    double i;
    int k = 0;
    double r;

    i = 60;
    data->rx = data->px + data->pixel / 6;
    data->ry = data->py + data->pixel / 6;
    r = i / WIDTH;
    data->r_angle = data->angle + 30;
    while (i > 0)
    {
        data->r_angle -= r;
        y = data->ry;
        x = data->rx;
        length = 0;
        while(y >= 0 && y < data->height && x >= 0 && x < data->width
            && data->map_s->map[(int)(y / data->pixel)][(int)(x / data->pixel)]
            && data->map_s->map[(int)(y / data->pixel)][(int)(x / data->pixel)] != '1')
        {
            length++;
            my_mlx_pixel_put(data, x, y, 0xb9fba5, 0);
            x += cos(d_to_r(data->r_angle));
            y -= sin(d_to_r(data->r_angle));
        }
        draw_ray_screen(data, length, k++);
        i -= r;
    }
}
