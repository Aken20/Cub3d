/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:47:54 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 01:25:37 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

float	d_to_r(float degree)
{
	while (degree < 0)
		degree += 360;
	while (degree > 360)
		degree -= 360;
	return (degree * (PI / 180));
}

int	wall_hit(float x, float y, t_data *data)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / data->map->pixel);
	y_m = floor (y / data->map->pixel);
	if (y_m < 0 || x_m < 0 || y_m >= data->map->height
		|| x_m >= (int)ft_strlen(data->map->map[y_m]))
		return (0);
	if (data->map->map[y_m] && x_m < (int)ft_strlen(data->map->map[y_m]))
		if (data->map->map[y_m][x_m] != '1' && data->map->map[y_m][x_m] != 'D'
			&& data->map->map[y_m][x_m] != 'U'
			&& data->map->map[y_m][x_m] != 'F')
			return (1);
	return (0);
}

int	wall_hit_2(float x, float y, t_data *data)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / data->map->pixel);
	y_m = floor (y / data->map->pixel);
	if (y_m < 0 || x_m < 0 || y_m >= data->map->height
		|| x_m >= (int)ft_strlen(data->map->map[y_m]))
		return (0);
	if (data->map->map[y_m] && x_m < (int)ft_strlen(data->map->map[y_m]))
		return (1);
	return (0);
}

void	draw_ray_screen(t_data *data, float length)
{
	float	h_dist;
	float	v_dist;
	bool	is_vert;

	is_vert = false;
	h_dist = roundf(get_hor_dest(data) * 100) / 100;
	v_dist = roundf(get_vert_dest(data) * 100) / 100;
	if (h_dist > 0 && h_dist < v_dist)
		length = h_dist;
	else
	{
		length = v_dist;
		is_vert = 1;
	}
	length = (length * cos(d_to_r(data->r_angle - data->map->angle))) * 1.6;
	data->line_height = (data->map->pixel / length)
		* ((WIDTH / 2) / tan(d_to_r(60) / 2));
	length = (data->map->pixel / length) * ((WIDTH / 2) / tan(d_to_r(60) / 2));
	data->end = (HEIGHT / 2) + ((int)length / 2);
	data->start = (HEIGHT / 2) - ((int)length / 2);
	if (data->end > HEIGHT)
		data->end = HEIGHT;
	if (data->start < 0)
		data->start = 0;
	draw_textures(data, is_vert, data->line_height);
}

void	draw_ray(t_data *data)
{
	float	length;
	float	fov;
	float	r;

	fov = 60;
	length = 0;
	data->x_screen = 0;
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
		draw_ray_screen(data, length);
		data->x_screen++;
		fov -= r;
	}
}
