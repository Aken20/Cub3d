#include "Cub3d.h"

float d_to_r(int degree)
{
    return (degree * (PI / 180));
}

int wall_hit(float x, float y, t_data *data) // check the wall hit
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
    // printf("x: %f, y: %f\n", x, y);
	x_m = floor (x / data->map_s->pixel); // get the x position in the map
	y_m = floor (y / data->map_s->pixel); // get the y position in the map
	if (y_m < 0 || x_m < 0 || y_m >= data->map_s->map_height || x_m >= (int)ft_strlen(data->map_s->map[y_m]))
		return (0);
    // printf("x_m: %d, y_m: %d\n", x_m, y_m);
	if (data->map_s->map[y_m] && x_m < (int)ft_strlen(data->map_s->map[y_m]))
		if (data->map_s->map[y_m][x_m] != '1')
			return (1);
	return (0);
}

void fill_vector(t_data *data, bool is_vert)
{
    float yo, xo, x, y;
    int p;

    x = data->map_s->rx;
    y = data->map_s->ry;
    if (is_vert)
    {
        yo = data->map_s->pixel * tan(d_to_r(data->r_angle));
        xo = data->map_s->pixel;
        if (!(data->r_angle > 90 && data->r_angle < 270))
            p = -1;
        else
            xo *= -1, p = 1;
        if ((yo < 0 && (data->r_angle > 0 && data->r_angle < 180))
            || (yo > 0 && !(data->r_angle > 0 && data->r_angle < 180)))
            yo *= -1;
        yo = -yo;
        while(wall_hit(x, y - p, data) && (int)(y) != (int)data->vy && (int)(x) != (int)data->vx)
        {
            my_mlx_pixel_put(data->mini_map, x, y - p, 0x0000fa);
            x += xo / data->map_s->pixel;
            y += yo / data->map_s->pixel;
        }
    }
    else
    {
        yo = data->map_s->pixel;
        xo = data->map_s->pixel / tan(d_to_r(data->r_angle));
        if ((xo > 0 && data->r_angle > 90 && data->r_angle < 270)
            || (xo < 0 && !(data->r_angle > 90 && data->r_angle < 270)))
            xo *= -1;
        if (!(data->r_angle > 0 && data->r_angle < 180))
            p = -1;
        else
            yo = -yo, p = 1;
        while(wall_hit(x - p, y, data) && (int)(y) != (int)data->hy && (int)(x) != (int)data->hx)
        {
            my_mlx_pixel_put(data->mini_map, x - p, y, 0xff0000);
            x += xo / data->map_s->pixel;
            y += yo / data->map_s->pixel;
        }
    }
}

float get_vert_dest(t_data *data)
{
    float yo, xo, vx, vy;
    int p;
    if (data->r_angle == 90 || data->r_angle == 270)
        return 100000;
    data->vx = data->map_s->rx;
    data->vy = data->map_s->ry;
    yo = data->map_s->pixel * tan(d_to_r(data->r_angle));
    xo = data->map_s->pixel;
    // yo = -yo;
    data->vx = floor(data->map_s->rx / data->map_s->pixel) * data->map_s->pixel;
    if (!(data->r_angle > 90 && data->r_angle < 270))
        data->vx += xo, p = -1;
    else
        xo *= -1, p = 1;
    data->vy = data->map_s->ry + (data->map_s->rx - data->vx) * tan(d_to_r(data->r_angle));
    if ((yo < 0 && (data->r_angle > 0 && data->r_angle < 180))
        || (yo > 0 && !(data->r_angle > 0 && data->r_angle < 180)))
        yo *= -1;
    // yo = -yo;
    vx = data->map_s->rx;
    vy = data->map_s->ry;
    while (wall_hit(data->vx, data->vy - p, data))
    {
        my_mlx_pixel_put(data->mini_map, data->vx, data->vy - p, 0x0000fa);
        data->vx += xo;
        data->vy += yo;
    }
    return (sqrt(data->map_s->rx - data->vx) * (data->map_s->rx - data->vx) + (data->map_s->ry - data->vy) * (data->map_s->ry - data->vy));
}

float get_hor_dest(t_data *data)
{
    float yo, xo, hx, hy;
    int p;
    data->hx = data->map_s->rx;
    data->hy = data->map_s->ry;
    yo = data->map_s->pixel;
    xo = data->map_s->pixel / tan(d_to_r(data->r_angle));
    if ((xo > 0 && data->r_angle > 90 && data->r_angle < 270)
        || (xo < 0 && !(data->r_angle > 90 && data->r_angle < 270)))
        xo *= -1;
    data->hy = floor(data->map_s->ry / data->map_s->pixel) * data->map_s->pixel;
    if (!(data->r_angle > 0 && data->r_angle < 180))
        data->hy += yo, p = -1;
    else
        yo = -yo, p = 1;
    data->hx = data->map_s->rx + (data->map_s->ry - data->hy) / tan(d_to_r(data->r_angle));
    hx = data->map_s->rx;
    hy = data->map_s->ry;
    while (wall_hit(data->hx, data->hy - p, data))
    {
        while (wall_hit(hx, hy - p, data))
        {
            my_mlx_pixel_put(data->mini_map, hx, hy - p, 0xff0000);
            hx += xo / data->map_s->pixel;
            hy += yo / data->map_s->pixel;
        }
        my_mlx_pixel_put(data->mini_map, data->hx, data->hy - p, 0xff0000);
        data->hx += xo;
        data->hy += yo;
    }
    if (data->r_angle == 0 || data->r_angle == 180)
        return 100000;
    return sqrt((data->map_s->rx - data->hx) * (data->map_s->rx - data->hx) + (data->map_s->ry - data->hy) * (data->map_s->ry - data->hy));
}
void draw_ray_screen(t_data *data, int length, float x)
{
    double y;
    // double start;
    // double end;
    int color;

    // else
    // printf("hor: %f, vert: %f, angle %f\n", get_hor_dest(data), get_vert_dest(data), data->r_angle);
    if (get_hor_dest(data) < get_vert_dest(data) && get_hor_dest(data) > 0)
        length = get_hor_dest(data), color = 0x0000fa, fill_vector(data, 0);
    else
        length = get_vert_dest(data), color = 0xff0000, fill_vector(data, 1);
    // printf("1. length: %d\n", length);
    // length = (data->map_s->pixel / length) * (WIDTH);
    // printf("length: %d\n", length);
    // length *= (data->map_s->pixel / length);
    length *= (HEIGHT / data->height);
    // length -= (data->map_s->pixel / 3);
    // length = length * 2;
    // length = length * (HEIGHT / length);
    // length = HEIGHT - length;
    // printf("length: %i\n", length);
    if (length < 0)
        length = 0;
    // printf("y: %f, x: %f\n", y, x);
    y = (HEIGHT / 2) - (length / 2);
    // printf("2. y: %f, x: %f\n", y, x);
    if (length > HEIGHT)
        length = 0;
    // if (get_vert_dest(data))
    //     color = 0x0000fa;
    // else
        // color = 0xb9fba5;
    // rx = data->map_s->rx;
    // ry = data->map_s->ry;

	// length = (data->map_s->pixel / length) * ((WIDTH / 2) / tan(d_to_r(60) / 2)); // get the wall height
	// end = (HEIGHT / 2) + (length / 2); // get the bottom pixel
	// start = (HEIGHT / 2) - (length / 2); // get the top pixel
    // printf("start: %f, end: %f\n", start, end);
	// if (end > HEIGHT) // check the bottom pixel
	// 	end = HEIGHT;
	// if (start < 0) // check the top pixel
	// 	start = 0;
    while(length > 0)
    {
        printf("y: %f, x: %f, length: %d, r_angle: %f\n", y, x, length, data->r_angle);
        my_mlx_pixel_put(data->screen, x, y + length--, color);
    }

}

void draw_ray(t_data *data)
{
    float length = 0;
    float fov;
    int k = 0;
    float r;

    fov = 60;
    data->map_s->rx = data->map_s->px + data->map_s->pixel / 6;
    data->map_s->ry = data->map_s->py + data->map_s->pixel / 6;
    r = fov / WIDTH;
    data->r_angle = data->map_s->angle + (fov / 2);
    while (fov > 0)
    {
        data->r_angle -= r;
        draw_ray_screen(data, length, k++);
        fov -= r;
    }
}
