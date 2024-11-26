/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:36:43 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 08:10:34 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

void	draw_flame_animation_texure(t_data *data, bool is_vert, int line_height)
{
	if (data->flame_flag > 20000)
		data->flame_flag = 0;
	if (data->flame_flag >= 0 && data->flame_flag <= 10000)
		draw_wall(data, is_vert, line_height, data->flame[0]);
	else if (data->flame_flag >= 10000 && data->flame_flag <= 15000)
		draw_wall(data, is_vert, line_height, data->flame[1]);
	else if (data->flame_flag >= 15000 && data->flame_flag <= 20000)
		draw_wall(data, is_vert, line_height, data->flame[2]);
}

void	draw_door_animation_texure(t_data *data, bool is_vert, int line_height)
{
	if (data->door_flag > 35000)
		data->door_flag = 0;
	if (data->door_flag <= 0)
		draw_wall(data, is_vert, line_height, data->door[0]);
	else if (data->door_flag > 5000 && data->door_flag < 20000)
		draw_wall(data, is_vert, line_height, data->door[2]);
	else if (data->door_flag >= 1 && data->door_flag <= 5000)
	{
		draw_wall(data, is_vert, line_height, data->door[1]);
		data->door_flag++;
	}
	else if (data->door_flag >= 30000 && data->door_flag <= 35000)
	{
		draw_wall(data, is_vert, line_height, data->door[1]);
		data->door_flag++;
	}
}

void	draw_animation_vert_texure(t_data *data, int line_height,
	int x_m, int y_m)
{
	if (data->map->map[y_m][x_m] == 'F'
		|| data->map->map[y_m][x_m - 1] == 'F')
		draw_flame_animation_texure(data, 1, line_height);
	else if (data->map->map[y_m][x_m] == 'D'
	|| data->map->map[y_m][x_m - 1] == 'D'
	|| data->map->map[y_m][x_m] == 'U'
	|| data->map->map[y_m][x_m - 1] == 'U')
		draw_door_animation_texure(data, 1, line_height);
	else if (data->r_angle > 90 && data->r_angle < 270)
		draw_wall(data, 1, line_height, data->w_wall);
	else
		draw_wall(data, 1, line_height, data->e_wall);
}

void	draw_animation_hor_texure(t_data *data, int line_height,
	int x_m, int y_m)
{
	if (data->map->map[y_m][x_m] == 'F'
		|| data->map->map[y_m - 1][x_m] == 'F')
		draw_flame_animation_texure(data, 0, line_height);
	else if (data->map->map[y_m][x_m] == 'D'
	|| data->map->map[y_m - 1][x_m] == 'D'
	|| data->map->map[y_m][x_m] == 'U'
	|| data->map->map[y_m - 1][x_m] == 'U')
		draw_door_animation_texure(data, 0, line_height);
	else if (data->r_angle > 0 && data->r_angle < 180)
		draw_wall(data, 0, line_height, data->n_wall);
	else
		draw_wall(data, 0, line_height, data->s_wall);
}

void	draw_textures(t_data *data, bool is_vert, int line_height)
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
				&& x_m - 1 < (int)ft_strlen(data->map->map[y_m])))
			draw_animation_vert_texure(data, line_height, x_m, y_m);
	}
	else
	{
		x_m = floor ((int)data->hx / data->map->pixel);
		y_m = floor ((int)data->hy / data->map->pixel);
		if ((y_m < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m])
				&& y_m - 1 < data->map->height
				&& x_m < (int)ft_strlen(data->map->map[y_m - 1])))
			draw_animation_hor_texure(data, line_height, x_m, y_m);
	}
}
