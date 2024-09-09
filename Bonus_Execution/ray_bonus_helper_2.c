/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus_helper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:26:05 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 01:27:59 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

void	get_vert_dest_helper(t_data *data, float xo, float yo)
{
	while (wall_hit(data->vx - 1, data->vy, data)
		&& wall_hit(data->vx, data->vy, data))
	{
		data->vx += xo;
		data->vy += yo;
	}
}

void	get_hor_dest_helper(t_data *data, float xo, float yo)
{
	while (wall_hit(data->hx, data->hy - 1, data)
		&& wall_hit(data->hx, data->hy, data))
	{
		data->hx += xo;
		data->hy += yo;
	}
}

float	get_vert_dest(t_data *data)
{
	float	yo;
	float	xo;

	if (data->r_angle == 90 || data->r_angle == 270)
		return (100000);
	data->vx = data->map->rx;
	data->vy = data->map->ry;
	yo = data->map->pixel * tan(d_to_r(data->r_angle));
	xo = data->map->pixel;
	data->vx = floor(data->map->rx / data->map->pixel) * data->map->pixel;
	if (!(data->r_angle > 90 && data->r_angle < 270))
		data->vx += xo;
	else
		xo *= -1;
	data->vy = (data->map->ry + (data->map->rx - data->vx)
			* tan(d_to_r(data->r_angle)));
	if ((yo < 0 && (data->r_angle > 0 && data->r_angle < 180))
		|| (yo > 0 && !(data->r_angle > 0 && data->r_angle < 180)))
		yo *= -1;
	yo = -yo;
	get_vert_dest_helper(data, xo, yo);
	return (sqrt(pow(data->map->rx - data->vx, 2)
			+ pow(data->map->ry - data->vy, 2)));
}

float	get_hor_dest(t_data *data)
{
	float	yo;
	float	xo;

	if (data->r_angle == 0 || data->r_angle == 180 || data->r_angle == 360)
		return (100000);
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
	data->hx = (data->map->rx + (data->map->ry - data->hy)
			/ tan(d_to_r(data->r_angle)));
	get_hor_dest_helper(data, xo, yo);
	return (sqrt(pow(data->map->rx - data->hx, 2)
			+ pow(data->map->ry - data->hy, 2)));
}

void	draw_wall(t_data *data, bool is_vert, int line_height, t_img *img)
{
	float	x;
	float	y;
	float	y_step;
	int		color;

	y = 0;
	color = 0;
	y_step = (float)img->height / line_height;
	if (is_vert)
		x = ((float)((int)data->vy % data->map->pixel)
				/ (data->map->pixel)) * img->width;
	else
		x = ((float)((int)data->hx % data->map->pixel)
				/ (data->map->pixel)) * img->width;
	while (data->start < data->end)
	{
		color = my_mlx_pixel_get(img, x, y);
		my_mlx_pixel_put(data->screen, data->x_screen, data->start++, color);
		y += y_step;
	}
}
