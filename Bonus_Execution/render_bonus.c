# include "../Cub3d_bonus.h"

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

void ft_draw_cursor(t_data *data)
{
    float y;
    float x;
    int i;

    y = 0;
    x = 0;
    i = 0;
    while (i < 20)
    {
        my_mlx_pixel_put(data->mini_map, 100 + x, 100 + y, 0xa9b5fa);
        x += cos(d_to_r(data->map->angle));
        y -= sin(d_to_r(data->map->angle));
        i++;
    }
}

void ft_draw_player(t_data *data)
{
    int y;
    int x;

    y = 94;
    x = 94;
    while (y < 106)
    {
        while (x < 106)
        {
            my_mlx_pixel_put(data->mini_map, x, y, 0x0000fa);
            x++;
        }
        x = 94;
        y++;
    }
    ft_draw_cursor(data);
}

int is_in_range(float px, float py) {
    float distance;

    distance = sqrt(pow(100 - px, 2) + pow(100 - py, 2));
    if (distance <= 100)
        return 1;
    return 0;
}

void draw_minimap(t_data *data)
{
    int x;
    int y;
    int x_x;
    int y_y;


    x = ((data->map->rx / data->map->pixel) * data->mini_map_scale) - 100;
    y = ((data->map->ry / data->map->pixel) * data->mini_map_scale) - 100;
    // printf("x: %d, y: %d\n", x, y);
    x_x = 0;
    y_y = 0;
    // printf("i: %d\n", i);
    // printf("px: %f, py: %f\n", data->map->px, data->map->py);
    // printf("x: %d, y: %d\n", x, y);
    // printf("x: %d, y: %d\n", (int)((x_x + x)) / data->mini_map_scale, (y_y + y) / data->mini_map_scale);
    while (y_y < 200)
    {
        while (x_x < 200)
        {
            // printf("x: %d, y: %d\n", (x_x + x) / data->mini_map_scale, (y_y + y) / data->mini_map_scale);
            if ((x_x < 4 || y_y < 4 || x_x > 195 || y_y > 195) && is_in_range(x_x, y_y))
                my_mlx_pixel_put(data->mini_map, x_x, y_y, 0x000000);
            if ((y_y + y) / data->mini_map_scale >= 0 && (y_y + y) / data->mini_map_scale < data->map->height && is_in_range(x_x, y_y)
                && (x_x + x) / data->mini_map_scale >= 0 && (x_x + x) / data->mini_map_scale < (int)ft_strlen(data->map->map[(y_y + y) / data->mini_map_scale]))
            {
                // printf("map: %d\n", data->map->map[(y_y + y) / data->mini_map_scale][(x_x + x) / data->mini_map_scale]);
                // printf("x: %d, y: %d\n", x, y);
                if (data->map->map[(y_y + y) / data->mini_map_scale][(x_x + x) / data->mini_map_scale] == ' ')
                    my_mlx_pixel_put(data->mini_map, x_x, y_y, 0x0000fa);
                if ((data->map->map[(y_y + y) / data->mini_map_scale][(x_x + x) / data->mini_map_scale] == '1'
                    || data->map->map[(y_y + y) / data->mini_map_scale][(x_x + x) / data->mini_map_scale] == 'D'
                    || data->map->map[(y_y + y) / data->mini_map_scale][(x_x + x) / data->mini_map_scale] == 'F'))
                    my_mlx_pixel_put(data->mini_map, x_x, y_y, 0x00ff00);
                if ((data->map->map[(y_y + y) / data->mini_map_scale][(x_x + x) / data->mini_map_scale] == '0'
                    || data->map->map[(y_y + y) / data->mini_map_scale][(x_x + x) / data->mini_map_scale] == 'U'))
                    my_mlx_pixel_put(data->mini_map, x_x, y_y, 0x6a592b);
                // else if ((x_x + x) % data->mini_map_scale < 1 || (y_y + y) % data->mini_map_scale < 1 || !data->map->map[(y_y + y) / data->mini_map_scale][(int)((x_x + x)) / data->mini_map_scale])
                //     my_mlx_pixel_put(data->mini_map, x_x, y_y, 0x000000);
            }
            else if (is_in_range(x_x, y_y))
                my_mlx_pixel_put(data->mini_map, x_x, y_y, 0x0000fa);
            else
                my_mlx_pixel_put(data->mini_map, x_x, y_y, -1);
            x_x++;
        }
        x_x = 0;
        y_y++;
    }
    // i++;
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
    ft_hocks(data);
    draw_screen(data);
    draw_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->mini_map->img, WIDTH - 220, HEIGHT - 220);
    mlx_put_image_to_window(data->mlx, data->win, data->mini_map_frame->img, WIDTH - 240, HEIGHT - 240);
    return 0;
}