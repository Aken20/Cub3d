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
	x_m = floor (x / data->pixel); // get the x position in the map
	y_m = floor (y / data->pixel); // get the y position in the map
	if (y_m < 0 || x_m < 0 || y_m >= data->map_s->map_height || x_m >= (int)ft_strlen(data->map_s->map[y_m]))
		return (0);
    // printf("x_m: %d, y_m: %d\n", x_m, y_m);
	if (data->map_s->map[y_m] && x_m < (int)ft_strlen(data->map_s->map[y_m]))
		if (data->map_s->map[y_m][x_m] != '1')
			return (1);
	return (0);
}

float get_vert_dest(t_data *data)
{
    float yo, xo, vx, vy;
    int p;
    if (data->r_angle == 90 || data->r_angle == 270)
        return 100000;
    data->vx = data->rx;
    data->vy = data->ry;
    yo = data->pixel * tan(d_to_r(data->r_angle));
    xo = data->pixel;
    // yo = -yo;
    data->vx = floor(data->rx / data->pixel) * data->pixel;
    if (!(data->r_angle > 90 && data->r_angle < 270))
        data->vx += xo, p = -1;
    else
        xo *= -1, p = 1;
    data->vy = data->ry + (data->rx - data->vx) * tan(d_to_r(data->r_angle));
    if ((yo < 0 && (data->r_angle > 0 && data->r_angle < 180))
        || (yo > 0 && !(data->r_angle > 0 && data->r_angle < 180)))
        yo *= -1;
    yo = -yo;
    vx = data->rx;
    vy = data->ry;
    while (wall_hit(data->vx, data->vy - p, data))
    {
        while(wall_hit(vx, vy - p, data) && (int)(vy) != (int)data->vy && (int)(vx) != (int)data->vx)
        {
            my_mlx_pixel_put(data, vx, vy - p, 0xff0000, 0);
            vx += xo / data->pixel;
            vy += yo / data->pixel;
        }
        my_mlx_pixel_put(data, data->vx, data->vy - p, 0xff0000, 0);
        data->vx += xo;
        data->vy += yo;
    }
    // printf("vx: %f, vy: %f\n", data->vx, data->vy);
    // printf("rx: %f, ry: %f\n", data->rx, data->ry);
    return (sqrt(data->rx - data->vx) * (data->rx - data->vx) + (data->ry - data->vy) * (data->ry - data->vy));
}

float get_hor_dest(t_data *data)
{
    float yo, xo, hx, hy;
    int p;
    data->hx = data->rx;
    data->hy = data->ry;
    yo = data->pixel;
    xo = data->pixel / tan(d_to_r(data->r_angle));
    if ((xo > 0 && data->r_angle > 90 && data->r_angle < 270)
        || (xo < 0 && !(data->r_angle > 90 && data->r_angle < 270)))
        xo *= -1;
    data->hy = floor(data->ry / data->pixel) * data->pixel;
    if (!(data->r_angle > 0 && data->r_angle < 180))
        data->hy += yo, p = -1;
    else
        yo = -yo, p = 1;
    data->hx = data->rx + (data->ry - data->hy) / tan(d_to_r(data->r_angle));
    hx = data->rx;
    hy = data->ry;
    while (wall_hit(data->hx, data->hy - p, data))
    {
        while (wall_hit(hx, hy - p, data))
        {
            my_mlx_pixel_put(data, hx, hy - p, 0xff0000, 0);
            hx += xo / data->pixel;
            hy += yo / data->pixel;
        }
        my_mlx_pixel_put(data, data->hx, data->hy - p, 0xff0000, 0);
        data->hx += xo;
        data->hy += yo;
    }
    if (data->r_angle == 0 || data->r_angle == 180)
        return 100000;
    return sqrt((data->rx - data->hx) * (data->rx - data->hx) + (data->ry - data->hy) * (data->ry - data->hy));
}
void draw_ray_screen(t_data *data, int length, float x)
{
    double y;
    // double start;
    // double end;
    int color;

    // else
    // printf("hor: %f, vert: %f, angle %f\n", get_hor_dest(data), get_vert_dest(data), data->r_angle);
    // if (get_hor_dest(data) < get_vert_dest(data) && get_hor_dest(data) > 0)
    //     length = get_hor_dest(data), color = 0x0000fa;
    // else
        length = get_vert_dest(data), color = 0xff0000;
    // printf("1. length: %d\n", length);
    // length = (data->pixel / length) * (WIDTH);
    // printf("length: %d\n", length);
    // length *= (data->pixel / length);
    length *= (HEIGHT / data->height);
    // length -= (data->pixel / 3);
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
    // rx = data->rx;
    // ry = data->ry;

	// length = (data->pixel / length) * ((WIDTH / 2) / tan(d_to_r(60) / 2)); // get the wall height
	// end = (HEIGHT / 2) + (length / 2); // get the bottom pixel
	// start = (HEIGHT / 2) - (length / 2); // get the top pixel
    // printf("start: %f, end: %f\n", start, end);
	// if (end > HEIGHT) // check the bottom pixel
	// 	end = HEIGHT;
	// if (start < 0) // check the top pixel
	// 	start = 0;
    while(length > 0)
    {
        // printf("y: %f, x: %f, length: %d, r_angle: %f\n", y, x, length, data->r_angle);
        // start++;
        // my_mlx_pixel_put(data, x, y + length, color, 1);
        // if ((ry - sin(d_to_r(data->r_angle))) >= 0 && (ry - sin(d_to_r(data->r_angle))) <= data->height && (rx + cos(d_to_r(data->r_angle)))>= 0 && (rx + cos(d_to_r(data->r_angle)))<= data->width
        //     && data->map_s->map[(int)(ry - sin(d_to_r(data->r_angle)))/ data->pixel][(int)(rx + cos(d_to_r(data->r_angle)))/ data->pixel]
        //     && data->map_s->map[(int)(ry - sin(d_to_r(data->r_angle)))/ data->pixel][(int)(rx + cos(d_to_r(data->r_angle)))/ data->pixel] != '1')
            my_mlx_pixel_put(data, x, y + length--, color, 1);
        // printf("rx: %f, ry: %f, length: %d\n", rx, ry, length);
        // x += cos(d_to_r(data->r_angle));
        // y -= sin(d_to_r(data->r_angle));
    }

}

void draw_ray(t_data *data)
{
    // float y;
    // float x;
    float length = 0;
    float fov;
    int k = 0;
    float r;

    fov = 60;
    data->rx = data->px + data->pixel / 6;
    data->ry = data->py + data->pixel / 6;
    r = fov / WIDTH;
    data->r_angle = data->angle + (fov / 2);
    while (fov > 0)
    {
        data->r_angle -= r;
        // y = data->ry;
        // x = data->rx;
        // while((y - sin(d_to_r(data->r_angle))) >= 0 && (y - sin(d_to_r(data->r_angle)))<= data->height && (x + cos(d_to_r(data->r_angle)))>= 0 && (x + cos(d_to_r(data->r_angle)))<= data->width
        //     && data->map_s->map[(int)(y - sin(d_to_r(data->r_angle)))/ data->pixel][(int)(x + cos(d_to_r(data->r_angle)))/ data->pixel]
        //     && data->map_s->map[(int)(y - sin(d_to_r(data->r_angle)))/ data->pixel][(int)(x + cos(d_to_r(data->r_angle)))/ data->pixel] != '1')
        // {
            // my_mlx_pixel_put(data, x, y, 0xff0000, 0);
            // x += cos(d_to_r(data->r_angle));
            // y -= sin(d_to_r(data->r_angle));
        // }
        // length = sqrt((data->rx - x) * (data->rx - x) + (data->ry - y) * (data->ry - y));
        // length = get_hor_dest(data);
        // if (length > get_vert_dest(data))
        //     length = get_vert_dest(data);
        // length *= cos(d_to_r(data->r_angle - data->angle));
        // if (length <= 0)
        //     length = 20;
        // printf("length: %f\n", length);
        draw_ray_screen(data, length, k++);
        fov -= r;
    }
}
