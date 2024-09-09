/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:36:43 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/09 07:02:52 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

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
	while (wall_hit(data->vx - 1, data->vy, data)
		&& wall_hit(data->vx, data->vy, data))
	{
		data->vx += xo;
		data->vy += yo;
	}
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
	while (wall_hit(data->hx, data->hy - 1, data)
		&& wall_hit(data->hx, data->hy, data))
	{
		data->hx += xo;
		data->hy += yo;
	}
	return (sqrt(pow(data->map->rx - data->hx, 2)
			+ pow(data->map->ry - data->hy, 2)));
}

void	draw_wall(t_data *data, bool is_vert, int k, int line_height, t_img *img)
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
		my_mlx_pixel_put(data->screen, k, data->start++, color);
		y += y_step;
	}
}

void	draw_textures(t_data *data, bool is_vert, int k, int line_height)
{
	int	x_m;
	int	y_m;

	data->flame_flag++;
	if (is_vert)
	{
		x_m = floor ((int)data->vx / data->map->pixel);
		y_m = floor ((int)data->vy / data->map->pixel);
		if ((y_m < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m])
				&& x_m - 1 < (int)ft_strlen(data->map->map[y_m]))
			&& (data->map->map[y_m][x_m] == 'F'
			|| data->map->map[y_m][x_m - 1] == 'F'))
		{
			if (data->flame_flag > 20000)
				data->flame_flag = 0;
			if (data->flame_flag >= 0 && data->flame_flag <= 10000)
				draw_wall(data, is_vert, k, line_height, data->flame[0]);
			else if (data->flame_flag >= 10000 && data->flame_flag <= 15000)
				draw_wall(data, is_vert, k, line_height, data->flame[1]);
			else if (data->flame_flag >= 15000 && data->flame_flag <= 20000)
				draw_wall(data, is_vert, k, line_height, data->flame[2]);
		}
		if ((y_m < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m])
				&& x_m - 1 < (int)ft_strlen(data->map->map[y_m]))
			&& (data->map->map[y_m][x_m] == 'D'
			|| data->map->map[y_m][x_m - 1] == 'D'
			|| data->map->map[y_m][x_m] == 'U'
			|| data->map->map[y_m][x_m - 1] == 'U'))
		{
			if (data->door_flag > 45000)
				data->door_flag = 0;
			if (data->door_flag <= 0)
				draw_wall(data, is_vert, k, line_height, data->door[0]);
			else if (data->door_flag > 25000 && data->door_flag < 30000)
				draw_wall(data, is_vert, k, line_height, data->door[3]);
			if (data->door_flag >= 1 && data->door_flag <= 10000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[0]);
				data->door_flag++;
			}
			else if (data->door_flag >= 10000 && data->door_flag <= 15000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[1]);
				data->door_flag++;
			}
			else if (data->door_flag >= 15000 && data->door_flag <= 20000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[2]);
				data->door_flag++;
			}
			else if (data->door_flag >= 20000 && data->door_flag <= 25000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[3]);
				data->door_flag++;
			}
			else if (data->door_flag >= 30000 && data->door_flag <= 35000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[2]);
				data->door_flag++;
			}
			else if (data->door_flag >= 35000 && data->door_flag <= 40000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[1]);
				data->door_flag++;
			}
			else if (data->door_flag >= 40000 && data->door_flag <= 45000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[0]);
				data->door_flag++;
			}
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
		if ((y_m < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m])
				&& y_m - 1 < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m - 1]))
			&& (data->map->map[y_m - 1][x_m] == 'F'
			|| data->map->map[y_m][x_m] == 'F'))
		{
			if (data->flame_flag > 20000)
				data->flame_flag = 0;
			if (data->flame_flag >= 0 && data->flame_flag <= 10000)
				draw_wall(data, is_vert, k, line_height, data->flame[0]);
			else if (data->flame_flag >= 10000 && data->flame_flag <= 15000)
				draw_wall(data, is_vert, k, line_height, data->flame[1]);
			else if (data->flame_flag >= 15000 && data->flame_flag <= 20000)
				draw_wall(data, is_vert, k, line_height, data->flame[2]);
		}
		if ((y_m < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m])
				&& y_m - 1 < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m - 1]))
			&& (data->map->map[y_m - 1][x_m] == 'D'
			|| data->map->map[y_m][x_m] == 'D'
			|| data->map->map[y_m - 1][x_m] == 'U'
			|| data->map->map[y_m][x_m] == 'U'))
		{
			if (data->door_flag > 45000)
				data->door_flag = 0;
			if (data->door_flag <= 0)
				draw_wall(data, is_vert, k, line_height, data->door[0]);
			else if (data->door_flag > 25000 && data->door_flag < 30000)
				draw_wall(data, is_vert, k, line_height, data->door[3]);
			if (data->door_flag >= 1 && data->door_flag <= 10000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[0]);
				data->door_flag++;
			}
			else if (data->door_flag >= 10000 && data->door_flag <= 15000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[1]);
				data->door_flag++;
			}
			else if (data->door_flag >= 15000 && data->door_flag <= 20000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[2]);
				data->door_flag++;
			}
			else if (data->door_flag >= 20000 && data->door_flag <= 25000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[3]);
				data->door_flag++;
			}
			else if (data->door_flag >= 30000 && data->door_flag <= 35000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[2]);
				data->door_flag++;
			}
			else if (data->door_flag >= 35000 && data->door_flag <= 40000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[1]);
				data->door_flag++;
			}
			else if (data->door_flag >= 40000 && data->door_flag <= 45000)
			{
				draw_wall(data, is_vert, k, line_height, data->door[0]);
				data->door_flag++;
			}
		}
		else if (data->r_angle > 0 && data->r_angle < 180)
			draw_wall(data, is_vert, k, line_height, data->N_Wall);
		else
			draw_wall(data, is_vert, k, line_height, data->S_Wall);
	}
}
