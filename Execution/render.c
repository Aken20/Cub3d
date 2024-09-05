#include "../Cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
        return ;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int my_mlx_pixel_get(t_img *img, int x, int y)
{
    char *dst;
    int color = 0;

    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return (color);
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    color = (*(unsigned int*)dst);
    return (color);
}

void ft_draw_player(t_data *data)
{
    int y;
    int x;
    int pixel;

    pixel = data->map->pixel / 3;
    y = 0;
    x = 0;


    while (y < pixel)
    {
        while (x < pixel)
        {
            my_mlx_pixel_put(data->mini_map, data->map->px + x, data->map->py + y, 0x0000fa);
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
        while (x < data->width && data->map->map[y / data->map->pixel][x / data->map->pixel])
        {
            // printf("x: %d, y: %d\n", x, y);
            if (data->map->map[y / data->map->pixel][x / data->map->pixel] == '1')
                my_mlx_pixel_put(data->mini_map, x, y, 0x80FF33);
            else
                my_mlx_pixel_put(data->mini_map, x, y, 0xc8c8cc);
            if (x % data->map->pixel < 1 || y % data->map->pixel < 1 || !data->map->map[y / data->map->pixel][x / data->map->pixel])
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
                my_mlx_pixel_put(data->screen, x, y, data->map->ceiling);
            else
                my_mlx_pixel_put(data->screen, x, y, data->map->floor);
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
    return 0;
}