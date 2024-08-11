#include "Cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->img_s->addr + (y * data->img_s->line_length + x * (data->img_s->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
void ft_draw_player(t_data *data)
{
    int y;
    int x;
    int pixel;

    pixel = data->pixel / 3;
    y = 0;
    x = 0;


    while (y <= pixel)
    {
        while (x <= pixel)
        {
            my_mlx_pixel_put(data, data->px + x, data->py + y, 0x0000fa);
            x++;
        }
        x = 0;
        y++;
    }
    while (pixel > 0)
    {
        my_mlx_pixel_put(data, data->rx, data->ry - pixel, 0x000000);
        pixel--;
    }
}

void draw_ray(t_data *data)
{
    int y;
    int x;
    int pixel;

    pixel = data->pixel / 3;
    y = 0;
    x = 0;

    while (pixel > 0)
    {
        my_mlx_pixel_put(data, data->rx, data->ry - pixel, 0x000000);
        pixel--;
    }
}

int ft_render(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    mlx_clear_window(data->mlx, data->win);
    while (y < data->height)
    {
        while (x < data->width && data->map_s->map[y / data->pixel][x / data->pixel])
        {
            if (data->map_s->map[y / data->pixel][x / data->pixel] == '1')
                my_mlx_pixel_put(data, x, y, 0x80FF33);
            else
                my_mlx_pixel_put(data, x, y, 0xc8c8cc);
            if (x % data->pixel < 1 || y % data->pixel < 1)
                my_mlx_pixel_put(data, x, y, 0x000000);
            x++;
        }
        x = 0;
        y++;
    }
    ft_draw_player(data);
    // draw_ray(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img_s->img, 0, 0);
    return 0;
}