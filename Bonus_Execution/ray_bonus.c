# include "../Cub3d_bonus.h"

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
		if (data->map->map[y_m][x_m] != '1' && data->map->map[y_m][x_m] != 'D' && data->map->map[y_m][x_m] != 'U')
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
    while (wall_hit(data->vx - 1, data->vy, data) && wall_hit(data->vx, data->vy, data))
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
    while (wall_hit(data->hx, data->hy - 1, data) && wall_hit(data->hx, data->hy, data))
    {
        // my_mlx_pixel_put(data->mini_map, data->hx, data->hy, 0xff0000);
        data->hx += xo;
        data->hy += yo;
    }
    return sqrt(pow(data->map->rx - data->hx, 2) + pow(data->map->ry - data->hy, 2));
}

static void draw_wall(t_data *data, bool is_vert, int k, int line_height, t_img *img)
{
    float   x;
    float   y;
    float y_step;
    int color;

    y = 0;
    color = 0;
    y_step = (float)img->height / line_height;
    if (is_vert)
        x = ((float)((int)data->vy % data->map->pixel) / (data->map->pixel)) * img->width;
    else
        x = ((float)((int)data->hx % data->map->pixel) / (data->map->pixel)) * img->width;
    while(data->start < data->end)
    {
        color = my_mlx_pixel_get(img, x, y);
        my_mlx_pixel_put(data->screen, k, data->start++, color);
        y += y_step;
    }
}


void     draw_textures(t_data *data, bool is_vert, int k, int line_height)
{
	int  x_m;
	int  y_m;

    if (is_vert)
    {
        x_m = floor ((int)data->vx / data->map->pixel);
        y_m = floor ((int)data->vy / data->map->pixel);
        if (data->map->map[y_m][x_m] == 'D' || data->map->map[y_m][x_m - 1] == 'D'
            || data->map->map[y_m][x_m] == 'U' || data->map->map[y_m][x_m - 1] == 'U')
        {
            if (data->door_flag > 45000)
                data->door_flag = 0;
            if (data->door_flag <= 0)
                draw_wall(data, is_vert, k, line_height, data->door[0]);
            else if(data->door_flag > 25000 && data->door_flag < 30000)
                draw_wall(data, is_vert, k, line_height, data->door[3]);
            if (data->door_flag >= 1 && data->door_flag <= 10000)
                draw_wall(data, is_vert, k, line_height, data->door[0]), data->door_flag++;
            else if (data->door_flag >= 10000 && data->door_flag <= 15000)
                draw_wall(data, is_vert, k, line_height, data->door[1]), data->door_flag++;
            else if (data->door_flag >= 15000 && data->door_flag <= 20000)
                draw_wall(data, is_vert, k, line_height, data->door[2]), data->door_flag++;
            else if (data->door_flag >= 20000 && data->door_flag <= 25000)
                draw_wall(data, is_vert, k, line_height, data->door[3]), data->door_flag++;
            else if (data->door_flag >= 30000 && data->door_flag <= 35000)
                draw_wall(data, is_vert, k, line_height, data->door[2]), data->door_flag++;
            else if (data->door_flag >= 35000 && data->door_flag <= 40000)
                draw_wall(data, is_vert, k, line_height, data->door[1]), data->door_flag++;
            else if (data->door_flag >= 40000 && data->door_flag <= 45000)
                draw_wall(data, is_vert, k, line_height, data->door[0]), data->door_flag++;
        }
        else if (data->r_angle > 90 && data->r_angle < 270)
            draw_wall(data, is_vert, k, line_height, data->W_Wall);
        else
            draw_wall(data, is_vert, k, line_height, data->E_Wall);
    }
    else
    {
        x_m = floor ((int)data->hx / data->map->pixel);
        y_m = floor ((int)data->hy / data->map->pixel);
        if (data->map->map[y_m - 1][x_m] == 'D' || data->map->map[y_m][x_m] == 'D'
            || data->map->map[y_m - 1][x_m] == 'U' || data->map->map[y_m][x_m] == 'U')
        {
            if (data->door_flag > 45000)
                data->door_flag = 0;
            if (data->door_flag <= 0)
                draw_wall(data, is_vert, k, line_height, data->door[0]);
            else if(data->door_flag > 25000 && data->door_flag < 30000)
                draw_wall(data, is_vert, k, line_height, data->door[3]);
            if (data->door_flag >= 1 && data->door_flag <= 10000)
                draw_wall(data, is_vert, k, line_height, data->door[0]), data->door_flag++;
            else if (data->door_flag >= 10000 && data->door_flag <= 15000)
                draw_wall(data, is_vert, k, line_height, data->door[1]), data->door_flag++;
            else if (data->door_flag >= 15000 && data->door_flag <= 20000)
                draw_wall(data, is_vert, k, line_height, data->door[2]), data->door_flag++;
            else if (data->door_flag >= 20000 && data->door_flag <= 25000)
                draw_wall(data, is_vert, k, line_height, data->door[3]), data->door_flag++;
            else if (data->door_flag >= 30000 && data->door_flag <= 35000)
                draw_wall(data, is_vert, k, line_height, data->door[2]), data->door_flag++;
            else if (data->door_flag >= 35000 && data->door_flag <= 40000)
                draw_wall(data, is_vert, k, line_height, data->door[1]), data->door_flag++;
            else if (data->door_flag >= 40000 && data->door_flag <= 45000)
                draw_wall(data, is_vert, k, line_height, data->door[0]), data->door_flag++;
        }
        else if (data->r_angle > 0 && data->r_angle < 180)
            draw_wall(data, is_vert, k, line_height, data->N_Wall);
        else
            draw_wall(data, is_vert, k, line_height, data->S_Wall);
    }
}

void draw_ray_screen(t_data *data, float length, float x)
{
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
        //     fill_vector(data, is_vert);
    }
    else
    {
        length = v_dist;
        is_vert = 1;
        // if ((int)data->r_angle == (int)data->map->angle)
        //     fill_vector(data, is_vert);
    }
    length *= cos(d_to_r(data->r_angle - data->map->angle));
    length *= 2;
    int line_height = (data->map->pixel / length) * ((WIDTH / 2) / tan(d_to_r(60) / 2));
	length = (data->map->pixel / length) * ((WIDTH / 2) / tan(d_to_r(60) / 2));
    data->end = (HEIGHT / 2) + ((int)length / 2);
	data->start = (HEIGHT / 2) - ((int)length / 2);
	if (data->end > HEIGHT)
		data->end = HEIGHT;
	if (data->start < 0)
		data->start = 0;
    draw_textures(data, is_vert, x, line_height);
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
