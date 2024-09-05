#include "../Cub3d.h"

float d_to_r(float degree)
{
    while (degree < 0)
        degree += 360;
    while (degree > 360)
        degree -= 360;
    return (degree * (PI / 180));
}

int wall_hit(float x, float y, t_data *data)
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / data->map->pixel);
	y_m = floor (y / data->map->pixel);
	if (y_m < 0 || x_m < 0 || y_m >= data->map->height || x_m >= (int)ft_strlen(data->map->map[y_m]))
		return (0);
	if (data->map->map[y_m] && x_m < (int)ft_strlen(data->map->map[y_m]))
		if (data->map->map[y_m][x_m] != '1')
            return (1);
	return (0);
}

int wall_hit_2(float x, float y, t_data *data)
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / data->map->pixel);
	y_m = floor (y / data->map->pixel);
	if (y_m < 0 || x_m < 0 || y_m >= data->map->height || x_m >= (int)ft_strlen(data->map->map[y_m]))
		return (0);
	if (data->map->map[y_m] && x_m < (int)ft_strlen(data->map->map[y_m]))
        return (1);
	return (0);
}

void fill_vector(t_data *data, bool is_vert)
{
    float yo, xo, x, y;
    float p;

    x = data->map->rx;
    y = data->map->ry;
    if (is_vert)
    {
        yo = data->map->pixel * tan(d_to_r(data->r_angle));
        xo = data->map->pixel;
        if (!(data->r_angle > 90 && data->r_angle < 270))
            p = 1;
        else
            xo *= -1, p = -1;
        if ((yo < 0 && (data->r_angle > 0 && data->r_angle < 180))
            || (yo > 0 && !(data->r_angle > 0 && data->r_angle < 180)))
            yo *= -1;
        yo = -yo;
        while(wall_hit_2(x - p, y, data) && ((int)(y) != (int)data->vy || (int)(x) != (int)data->vx))
        {
            my_mlx_pixel_put(data->mini_map, x, y, 0xF6F633);
            if ((int)(x) != (int)data->vx)
                x += xo / (data->map->pixel * 10);
            if ((int)(y) != (int)data->vy)
                y += yo / (data->map->pixel * 10);
        }
    }
    else
    {
        yo = data->map->pixel;
        xo = data->map->pixel / tan(d_to_r(data->r_angle));
        if ((xo > 0 && data->r_angle > 90 && data->r_angle < 270)
            || (xo < 0 && !(data->r_angle > 90 && data->r_angle < 270)))
            xo *= -1;
        if (!(data->r_angle > 0 && data->r_angle < 180))
            p = 0.0001;
        else
            yo = -yo, p = -0.0001;
        while(wall_hit_2(x, y - p, data) && ((int)(y) != (int)data->hy || (int)(x) != (int)data->hx))
        {
            my_mlx_pixel_put(data->mini_map, x, y, 0xF6F633);
            if ((int)(x) != (int)data->hx)
                x += xo / (data->map->pixel * 10);
            if ((int)(y) != (int)data->hy)
                y += yo / (data->map->pixel * 10);
        }
    }
}

float get_vert_dest(t_data *data)
{
    float yo, xo;

    if (data->r_angle == 90 || data->r_angle == 270)
        return 100000;
    data->vx = data->map->rx;
    data->vy = data->map->ry;
    yo = data->map->pixel * tan(d_to_r(data->r_angle));
    xo = data->map->pixel;
    data->vx = floor(data->map->rx / data->map->pixel) * data->map->pixel;
    if (!(data->r_angle > 90 && data->r_angle < 270))
        data->vx += xo;
    else
        xo *= -1;
    data->vy = (data->map->ry + (data->map->rx - data->vx) * tan(d_to_r(data->r_angle)));
    if ((yo < 0 && (data->r_angle > 0 && data->r_angle < 180))
        || (yo > 0 && !(data->r_angle > 0 && data->r_angle < 180)))
        yo *= -1;
    yo = -yo;
    while (wall_hit(data->vx - 0.0001, data->vy, data) && wall_hit(data->vx, data->vy, data))
    {
        // my_mlx_pixel_put(data->mini_map, data->vx, data->vy, 0x0000fa);
        data->vx += xo;
        data->vy += yo;
    }
    return sqrt(pow(data->map->rx - data->vx, 2) + pow(data->map->ry - data->vy, 2));
}

float get_hor_dest(t_data *data)
{
    float yo, xo;

    if (data->r_angle == 0 || data->r_angle == 180 || data->r_angle == 360)
        return 100000;
    data->hx = data->map->rx;
    data->hy = data->map->ry;
    yo = data->map->pixel;
    xo = data->map->pixel / tan(d_to_r(data->r_angle));
    if ((xo > 0 && data->r_angle > 90 && data->r_angle < 270)
        || (xo < 0 && !(data->r_angle > 90 && data->r_angle < 270)))
        xo *= -1;
    data->hy = floor(data->map->ry / data->map->pixel) * data->map->pixel;
    if (!(data->r_angle > 0 && data->r_angle < 180))
        data->hy += yo;
    else
        yo = -yo;
    data->hx = (data->map->rx + (data->map->ry - data->hy) / tan(d_to_r(data->r_angle)));
    while (wall_hit(data->hx, data->hy - 0.0001, data) && wall_hit(data->hx, data->hy, data))
    {
        // my_mlx_pixel_put(data->mini_map, data->hx, data->hy, 0xff0000);
        data->hx += xo;
        data->hy += yo;
    }
    return sqrt(pow(data->map->rx - data->hx, 2) + pow(data->map->ry - data->hy, 2));
}

int     get_color(t_data *data, bool is_vert, float start, float end, int k, int line_height)
{
    int x;
    int   y;
    float y_step;
    int color;

    y = 0;
    if (is_vert)
    {
        if (data->r_angle > 90 && data->r_angle < 270)
        {
            x = ((float)((int)data->vy % data->map->pixel) / (data->map->pixel)) * data->W_Wall->width;
            y_step = (float)data->W_Wall->height / line_height;
            while(start < end)
            {
                color = my_mlx_pixel_get(data->W_Wall, x, y);
                my_mlx_pixel_put(data->screen, k, start++, color);
                y += y_step;
            }
        }
        else
        {
            x = ((float)((int)data->vy % data->map->pixel) / (data->map->pixel)) * data->E_Wall->width;
            y_step = (float)data->E_Wall->height / line_height;
            while(start < end)
            {
                // printf(" x: %d, y: %d\n", x, y);
                color = my_mlx_pixel_get(data->E_Wall, x, y);
                my_mlx_pixel_put(data->screen, k, start++, color);
                y += y_step;
            }
        }
    }
    else
    {
        if (data->r_angle > 0 && data->r_angle < 180)
        {
            x = ((float)((int)data->hx % data->map->pixel) / (data->map->pixel)) * data->N_Wall->width;
            y_step = (float)data->N_Wall->height / line_height;
            while(start < end)
            {
                color = my_mlx_pixel_get(data->N_Wall, x, y);
                // printf("x: %d, y: %d, color: %d\n", x, y, color);
                my_mlx_pixel_put(data->screen, k, start++, color);
                y += y_step;
            }
        }
        else
        {
            x = ((float)((int)data->hx % data->map->pixel) / (data->map->pixel)) * data->S_Wall->width;
            y_step = (float)data->S_Wall->height / line_height;
            while(start < end)
            {
                color = my_mlx_pixel_get(data->S_Wall, x, y);
                my_mlx_pixel_put(data->screen, k, start++, color);
                y += y_step;
            }
        }
        // if ((int)data->r_angle == (int)data->map->angle)
        //     printf("x: %d, y: %d, color: %d\n", x, y, color);
    }
    return (color);
}
void draw_ray_screen(t_data *data, float length, float x)
{
    float start;
    float end;
    float h_dist;
    float v_dist;
    bool is_vert = false;

    h_dist = roundf(get_hor_dest(data) * 100) / 100;
    v_dist = roundf(get_vert_dest(data) * 100) / 100;
    if (h_dist > 0 && h_dist < v_dist)
    {
        length = h_dist;
        is_vert = 0;
        // if ((int)data->r_angle == (int)data->map->angle)
            fill_vector(data, is_vert);
    }
    else
    {
        length = v_dist;
        is_vert = 1;
        // if ((int)data->r_angle == (int)data->map->angle)
            fill_vector(data, is_vert);
    }
    length *= cos(d_to_r(data->r_angle - data->map->angle));
    int line_height = (data->map->pixel / length) * ((WIDTH / 2) / tan(d_to_r(60) / 2));
    if (length < 0)
    length = 0;
    if (length > HEIGHT)
        length = 0;
	length = (data->map->pixel / length) * ((WIDTH / 2) / tan(d_to_r(60) / 2));
    end = (HEIGHT / 2) + ((int)length / 2);
	start = (HEIGHT / 2) - ((int)length / 2);
	if (end > HEIGHT)
		end = HEIGHT;
	if (start < 0)
		start = 0;
    get_color(data, is_vert, start, end, x, line_height);
}

void draw_ray(t_data *data)
{
    float length = 0;
    float fov;
    int k = 0;
    float r;

    fov = 60;
    data->map->rx = data->map->px + data->map->pixel / 6;
    data->map->ry = data->map->py + data->map->pixel / 6;
    r = fov / WIDTH;
    data->r_angle = data->map->angle + (fov / 2);
    if (data->r_angle > 360)
        data->r_angle -= 360;
    while (fov > 0)
    {
        data->r_angle -= r;
        if (data->r_angle < 0)
            data->r_angle += 360;
        draw_ray_screen(data, length, k++);
        fov -= r;
    }
}
