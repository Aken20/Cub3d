/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 03:30:31 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 03:32:01 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

float	d_to_r(float degree)
{
	while (degree < 0)
		degree += 360;
	while (degree > 360)
		degree -= 360;
	return (degree * (PI / 180));
}

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
