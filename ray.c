#include "Cub3d.h"

float d_to_r(int degree)
{
    return (degree * (PI / 180));
}

float get_vert_dest(t_data *data)
{
// int mx, my, mp, dof, side; float vx, vy, rx, ry, xo, yo, disV, disH;
    float yo, xo;
    int p;
    data->vx = data->rx;
    data->vy = data->ry;
    // printf("r_angle: %f\n", data->r_angle);
    yo = data->pixel * tan(d_to_r(data->r_angle));
    xo = data->pixel;
    if ((yo < 0 && data->r_angle < 90 && data->r_angle > 270)
        || (yo > 0 && (data->r_angle < 90 && data->r_angle > 270)))
        yo *= -1;
    data->vx = floor(data->rx / data->pixel) * data->pixel;
    if (!(data->r_angle > 90 && data->r_angle < 270))
        data->vx += xo, p = -1;
    else
        xo = -xo, p = 1;
    data->vy = data->ry + (data->vx - data->rx) * tan(d_to_r(data->r_angle));
    printf("vx: %f, vy: %f\n", data->vx, data->vy);
    printf("round(vy / pixel): %d, round(vx / pixel): %d\n", (int)round(data->vy / data->pixel), (int)round(data->vx / data->pixel));
    while ((int)round(data->vx - p / data->pixel) >= 0 && (int)round(data->vx - p / data->pixel) <= data->width / data->pixel
            && (int)round((data->vy / data->pixel)) >= 0 && (int)round((data->vy / data->pixel)) <= data->height / data->pixel
            && data->map_s->map[(int)round((data->vy / data->pixel))][(int)round(data->vx - p / data->pixel)]
            && data->map_s->map[(int)round((data->vy / data->pixel))][(int)round(data->vx - p / data->pixel)] != '1')
    {
        printf("vx: %f, vy: %f\n", data->vx, data->vy);
        my_mlx_pixel_put(data, data->vx, data->vy, 0x80FF33, 0);
        data->vx += xo;
        data->vy += yo;
        printf("vx: %f, vy: %f\n", data->vx, data->vy);
    }
    return (sqrt(data->rx - data->vx) * (data->rx - data->vx) + (data->ry - data->vy) * (data->ry - data->vy));
}

float get_hor_dest(t_data *data)
{
    float yo, xo;
    int p;
    data->hx = data->rx;
    data->hy = data->ry;
    yo = data->pixel;
    xo = data->pixel / tan(d_to_r(data->r_angle));
    if ((xo > 0 && data->r_angle > 90 && data->r_angle < 270)
        || (xo < 0 && !(data->r_angle > 90 && data->r_angle < 270)))
        xo *= -1;
    data->hy = floor(data->ry / data->pixel) * data->pixel;
    if (data->r_angle < 0 || data->r_angle > 180)
        data->hy += yo, p = -1;
    else
        yo = -yo, p = 1;
    data->hx = data->rx + (data->hy - data->ry) / tan(d_to_r(data->r_angle));
    while (data->hx + xo > 0 && data->hx + xo < data->width && (data->hy + yo) > 0 && (data->hy + yo) < data->height
            && data->map_s->map[(int)(data->hy + yo - p) / data->pixel][(int)(data->hx + xo) / data->pixel]
            && data->map_s->map[(int)(data->hy + yo - p) / data->pixel][(int)(data->hx + xo) / data->pixel] != '1')
    {
        printf("hx: %f, hy: %f, r_angle: %f\n", data->hx, data->hy, data->r_angle);
        my_mlx_pixel_put(data, data->hx, data->hy, 0x80FF33, 0);
        data->hx += xo;
        data->hy += yo;
        printf("hx: %f, hy: %f, r_angle: %f\n", data->hx, data->hy, data->r_angle);
        printf("xo: %f, yo: %f\n", xo, yo);
    }
    return sqrt((data->rx - data->hx) * (data->rx - data->hx) + (data->ry - data->hy) * (data->ry - data->hy));
}
void draw_ray_screen(t_data *data, int length, float x)
{
    float y;
    // float rx;
    // float ry;
    int color;

    // else
    length *= (HEIGHT / data->height);
    // length -= (data->pixel / 3);
    // length = length * 2;
    // length = length * (HEIGHT / length);
    length = HEIGHT - length;
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
        color = 0xb9fba5;
    // rx = data->rx;
    // ry = data->ry;
    while(length > 0)
    {
        // printf("y: %f, x: %f, length: %d, r_angle: %f\n", y, x, length, data->r_angle);
        length--;
        // my_mlx_pixel_put(data, x, y + length, color, 1);
        // if ((ry - sin(d_to_r(data->r_angle))) >= 0 && (ry - sin(d_to_r(data->r_angle))) <= data->height && (rx + cos(d_to_r(data->r_angle)))>= 0 && (rx + cos(d_to_r(data->r_angle)))<= data->width
        //     && data->map_s->map[(int)(ry - sin(d_to_r(data->r_angle)))/ data->pixel][(int)(rx + cos(d_to_r(data->r_angle)))/ data->pixel]
        //     && data->map_s->map[(int)(ry - sin(d_to_r(data->r_angle)))/ data->pixel][(int)(rx + cos(d_to_r(data->r_angle)))/ data->pixel] != '1')
            my_mlx_pixel_put(data, x, y + length, color, 1);
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
        //     // my_mlx_pixel_put(data, x, y, 0x000000, 0);
        //     x += cos(d_to_r(data->r_angle));
        //     y -= sin(d_to_r(data->r_angle));
        // }
        // length = sqrt(get_vert_dest(data) * get_vert_dest(data) + get_hor_dest(data) * get_hor_dest(data));
        // length = get_hor_dest(data);
        // if (length > get_vert_dest(data))
            length = get_vert_dest(data);
        if (length <= 0)
            length = 20;
        // printf("k: %d\n", k);
        draw_ray_screen(data, length, k++);
        fov -= r;
    }
}
