#include "Cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color, int i)
{
    char *dst;

    if (!i)
    {
        dst = data->img_s->addr + (y * data->img_s->line_length + x * (data->img_s->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
    else 
    {
        dst = data->img_s->s_addr + (y * data->img_s->s_line_length + x * (data->img_s->s_bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
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
            my_mlx_pixel_put(data, data->px + x, data->py + y, 0x0000fa, 0);
            x++;
        }
        x = 0;
        y++;
    }
}

static void draw_minimap(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < data->height)
    {
        while (x < data->width && data->map_s->map[y / data->pixel][x / data->pixel])
        {
            if (data->map_s->map[y / data->pixel][x / data->pixel] == '1')
                my_mlx_pixel_put(data, x, y, 0x80FF33, 0);
            else
                my_mlx_pixel_put(data, x, y, 0xc8c8cc, 0);
            if (x % data->pixel < 1 || y % data->pixel < 1 || !data->map_s->map[y / data->pixel][x / data->pixel])
                my_mlx_pixel_put(data, x, y, 0x000000, 0);
            x++;
        }
        x = 0;
        y++;
    }
}

static void draw_screen(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {
            if (y < HEIGHT / 2)
                my_mlx_pixel_put(data, x, y, data->img_s->celing, 1);
            else
                my_mlx_pixel_put(data, x, y, data->img_s->floor, 1);
            x++;
        }
        x = 0;
        y++;
    }
    ft_draw_player(data);
    draw_ray(data);
}

int ft_render(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    draw_minimap(data);
    draw_screen(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img_s->screen, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img_s->mini_map, 0, 0);
    return 0;
}