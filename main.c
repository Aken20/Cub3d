# include "Cub3d.h"

void    ft_free_data(t_data *data)
{
    free(data->map_s);
    free(data->img_s);
    free(data);
}

t_data *ft_init(void)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->map_s = malloc(sizeof(t_map));
    data->img_s = malloc(sizeof(t_imgs));
    data->map_s->map = malloc(sizeof(char*) * 6);
    data->pixel = 40;
    data->x = 4 * data->pixel;
    data->y = 3 * data->pixel;
    data->speed = 5;
    // data->map_s->map = (char*[]) { "111111","100101","101001","1100N1","111111", NULL };
    data->map_s->map[0] = ft_strdup("111111");
    data->map_s->map[1] = ft_strdup("100101");
    data->map_s->map[2] = ft_strdup("101001");
    data->map_s->map[3] = ft_strdup("1100N1");
    data->map_s->map[4] = ft_strdup("111111");
    data->map_s->map[5] = NULL;
    data->map_s->map_width = 6;
    data->map_s->map_height = 5;
    data->width = data->map_s->map_width * data->pixel;
    data->height = data->map_s->map_height * data->pixel;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3d");
    data->img_s->img = mlx_new_image(data->mlx, data->width, data->height);
    return (data);
}

int ft_quit_game(t_data *data)
{
    ft_free_data(data);
    exit(0);
}

int ft_up(t_data *data)
{
    if (data->y - data->speed > 0 && data->map_s->map[(data->y - data->speed) / data->pixel][data->x / data->pixel] != '1')
    {
        // printf("x: %d, y: %d\n", data->x, data->y);
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = '0';
        data->y -= data->speed;
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = 'N';
    }
    return 0;
}

int ft_down(t_data *data)
{
    if ((data->y + data->speed) < data->height && data->map_s->map[(data->y + data->speed) / data->pixel][data->x / data->pixel] != '1')
    {
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = '0';
        data->y += data->speed;
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = 'N';
    }
    return 0;
}

int ft_left(t_data *data)
{
    if (data->x - data->speed > 0 && data->map_s->map[data->y / data->pixel][(data->x - data->speed) / data->pixel] != '1')
    {
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = '0';
        data->x -= data->speed;
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = 'N';
    }
    return 0;
}

int ft_right(t_data *data)
{
    if ((data->x + data->speed) < data->width && data->map_s->map[data->y / data->pixel][(data->x + data->speed) / data->pixel] != '1')
    {
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = '0';
        data->x += data->speed;
        data->map_s->map[data->y / data->pixel][data->x / data->pixel] = 'N';
    }
    return 0;
}

int ft_hocks(int keycode, t_data *data)
{
    // printf("keycode: %d\n", keycode);
    if (keycode == 113)
        ft_quit_game(data);
    if (keycode == 119)
        return (ft_up(data));
    if (keycode == 115)
        return (ft_down(data));
    if (keycode == 97)
        return (ft_left(data));
    if (keycode == 100)
        return (ft_right(data));
    return 0;
}

int ft_render(t_data *data)
{
    int x;
    int y;
    static int s;

    x = 0;
    y = 0;

    if (s == 25)
    {
        mlx_clear_window(data->mlx, data->win);
        s = 0;
    }
    // printf("width: %d\n", data->width);
    // printf("height: %d\n", data->height);
    while(y < data->height)
    {
        while(x < data->width)
        {
            // printf("i: %d, j: %d\n", i, j);
            if (y >= data->height || x >= data->width)
                break;
            // printf("i: %d, j: %d\n", y / data->pixel, x / data->pixel);
            if (data->map_s->map[y / data->pixel][x / data->pixel] == '1')
                mlx_pixel_put(data->mlx, data->win, x, y, 0x80FF33);
            else if (data->map_s->map[y / data->pixel][x / data->pixel] == 'N')
                mlx_pixel_put(data->mlx, data->win, x, y, 0xea233b);
            x++;
        }
        x = 0;
        y++;
    }
    s++;
    return 0;
}

int main()
{
    t_data *data;

    data = ft_init();

    ft_render(data);
    mlx_loop_hook(data->mlx, ft_render, data);
    // mlx_hook(data->win, 2, 0, ft_hocks, data);
    mlx_hook(data->win, 17, 0, ft_quit_game, data);
    mlx_key_hook(data->win, ft_hocks, data);
    mlx_loop(data->mlx);
}