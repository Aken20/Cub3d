# include "Cub3d.h"


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->img_s->addr + (y * data->img_s->line_length + x * (data->img_s->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    ft_free_data(t_data *data)
{
    free(data->map_s);
    free(data->img_s);
    free(data);
}

void ft_read_map(t_data *img, char *file)
{
    int fd;

    char *line;
    int i;

    i = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\n");
        exit(0);
    }
    line = get_next_line(fd);
    while (line)
    {
        img->map_s->map_height++;
        i = ft_strlen(line);
        if (i > img->map_s->map_width)
            img->map_s->map_width = i;
        free(line);
        line = get_next_line(fd);
    }
    // img->map_s->map_height--;
    // printf("map_width: %d, map_height: %d\n", img->map_s->map_width, img->map_s->map_height);
    close(fd);
    fd = open(file, O_RDONLY);
    if (fd < 0 || img->map_s->map_height <= 1)
    {
        printf("Error\n");
        exit(0);
    }
    img->map_s->map = malloc(sizeof(char*) * (img->map_s->map_height + 1));
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        img->map_s->map[i++] = line;
        line = get_next_line(fd);
    }
    img->map_s->map[i] = NULL;
    close(fd);
}

void ft_draw_player(t_data *data)
{
    int y;
    int x;
    int pixel;

    pixel = data->pixel / 3;
    y = 0;
    x = 0;

    while (y < pixel)
    {
        while (x < pixel)
        {
            my_mlx_pixel_put(data, data->px + x, data->py + y, 0x0000fa);
            x++;
        }
        x = 0;
        y++;
    }
}

t_data *ft_init(char *file)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->map_s = malloc(sizeof(t_map));
    data->img_s = malloc(sizeof(t_imgs));
    data->pixel = 20;
    data->px = 4 * data->pixel + (data->pixel / 3);
    data->py = 3 * data->pixel + (data->pixel / 3);
    data->speed = 5;
    data->map_s->map_width = 0;
    data->map_s->map_height = 0;
    ft_read_map(data, file);
    data->width = data->map_s->map_width * data->pixel;
    data->height = data->map_s->map_height * data->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3d");
    data->img_s->img = mlx_new_image(data->mlx, data->width, data->height);
    data->img_s->addr = mlx_get_data_addr(data->img_s->img, &data->img_s->bits_per_pixel, &data->img_s->line_length, &data->img_s->endian);
    return (data);
}

int ft_quit_game(t_data *data)
{
    ft_free_data(data);
    exit(0);
}

int ft_up(t_data *data)
{
    if (data->py - data->speed > 0 && data->map_s->map[(data->py - data->speed) / data->pixel][data->px / data->pixel] != '1')
    {
        // printf("x: %d, y: %d\n", data->px, data->py);
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->py -= data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    
    return 0;
}

int ft_down(t_data *data)
{
    if ((data->py + data->speed + (data->pixel / 3)) < data->height && data->map_s->map[(data->py + data->speed + (data->pixel / 3)) / data->pixel][data->px / data->pixel] != '1')
    {
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->py += data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    return 0;
}

int ft_left(t_data *data)
{
    if (data->px - data->speed > 0 && data->map_s->map[data->py / data->pixel][(data->px - data->speed) / data->pixel] != '1')
    {
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->px -= data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    return 0;
}

int ft_right(t_data *data)
{
    if ((data->px + data->speed + (data->pixel / 3)) < data->width && data->map_s->map[data->py / data->pixel][(data->px + data->speed + (data->pixel / 3)) / data->pixel] != '1')
    {
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = '0';
        data->px += data->speed;
        data->map_s->map[data->py / data->pixel][data->px / data->pixel] = 'N';
    }
    return 0;
}

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == ESC)
        ft_quit_game(data);
    if (keycode == W)
        // data->py -= data->speed;
        return (ft_up(data));
    if (keycode == S)
        // data->py += data->speed;
        return (ft_down(data));
    if (keycode == A)
        // data->px -= data->speed;
        return (ft_left(data));
    if (keycode == D)
        // data->px += data->speed;
        return (ft_right(data));
    return 0;
}

int ft_render(t_data *data)
{
    int x;
    int y;
    // static int s;

    x = 0;
    y = 0;

    // if (s == 25)
    // {
        mlx_clear_window(data->mlx, data->win);
    //     s = 0;
    // }
    // printf("width: %d\n", data->width);
    // printf("height: %d\n", data->height);
    while (y < data->height)
    {
        while (x < data->width && data->map_s->map[y / data->pixel][x / data->pixel])
        {
            // printf("y: %d, x: %d\n", y, x);
            // printf("pixel: %d\n", data->pixel);
            // printf("y: %d, x: %d\n", y / data->pixel, x / data->pixel);
            // printf("width: %d, hight: %d\n", data->width, data->height);
            if (data->map_s->map[y / data->pixel][x / data->pixel] == '1')
                my_mlx_pixel_put(data, x, y, 0x80FF33);
            else
                my_mlx_pixel_put(data, x, y, 0xc8c8cc);
            // else if (data->map_s->map[y / data->pixel][x / data->pixel] == 'N')
            x++;
        }
        x = 0;
        y++;
    }
    ft_draw_player(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img_s->img, 0, 0);
    // s++;
    return 0;
}

int main(int ac, char **av)
{
    t_data *data;
    if (ac != 2)
    {
        printf("Error\n");
        exit(0);
    }
    data = ft_init(av[1]);
    // ft_render(data);
    mlx_loop_hook(data->mlx, ft_render, data);
    mlx_hook(data->win, 2, 0, ft_hocks, data);
    mlx_hook(data->win, 17, 0, ft_quit_game, data);
    // mlx_key_hook(data->win, ft_hocks, data);
    mlx_loop(data->mlx);
}