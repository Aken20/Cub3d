#include "Cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// int my_mlx_pixel_get(t_data *data, int x, int y, int color, int i)
// {
//     char *dst;

//     if (!i)
//     {
//         dst = data->img_s->addr + (y * data->img_s->line_length + x * (data->img_s->bits_per_pixel / 8));
//         *(unsigned int*)dst = color;
//     }
//     else 
//     {
//         dst = data->img_s->s_addr + (y * data->img_s->s_line_length + x * (data->img_s->s_bits_per_pixel / 8));
//         *(unsigned int*)dst = color;
//     }
// }

void ft_draw_player(t_data *data)
{
    int y;
    int x;
    int pixel;

    pixel = data->map_s->pixel / 3;
    y = 0;
    x = 0;


    while (y < pixel)
    {
        while (x < pixel)
        {
            my_mlx_pixel_put(data->mini_map, data->map_s->px + x, data->map_s->py + y, 0x0000fa);
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
        while (x < data->width && data->map_s->map[y / data->map_s->pixel][x / data->map_s->pixel])
        {
            if (data->map_s->map[y / data->map_s->pixel][x / data->map_s->pixel] == '1')
                my_mlx_pixel_put(data->mini_map, x, y, 0x80FF33);
            else
                my_mlx_pixel_put(data->mini_map, x, y, 0xc8c8cc);
            if (x % data->map_s->pixel < 1 || y % data->map_s->pixel < 1 || !data->map_s->map[y / data->map_s->pixel][x / data->map_s->pixel])
                my_mlx_pixel_put(data->mini_map, x, y, 0x000000);
            x++;
        }
        x = 0;
        y++;
    }
    ft_draw_player(data);
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
                my_mlx_pixel_put(data->screen, x, y, data->celing);
            else
                my_mlx_pixel_put(data->screen, x, y, data->floor);
            x++;
        }
        x = 0;
        y++;
    }
    draw_ray(data);
}

int ft_render(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    draw_minimap(data);
    draw_screen(data);
    mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->mini_map->img, 0, 0);
    // sleep(2);
    return 0;
}