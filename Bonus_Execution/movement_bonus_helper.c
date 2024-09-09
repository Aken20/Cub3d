/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:13:12 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/09 05:32:47 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

int	ft_mouse_hocks(int x, int y, t_data *data)
{
	static int	previous_x;

	if (x > previous_x)
	{
		previous_x = x;
		data->map->angle -= ((y * 0) + 3);
		if (data->map->angle < 0)
			data->map->angle += 360;
	}
	else
	{
		previous_x = x;
		data->map->angle += 3;
		if (data->map->angle > 360)
			data->map->angle -= 360;
	}
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_quit_game(data);
	if (keycode == SP)
		handel_door(data);
	if (keycode == W)
		data->keys.up = true;
	if (keycode == S)
		data->keys.down = true;
	if (keycode == A)
		data->keys.left = true;
	if (keycode == D)
		data->keys.right = true;
	if (keycode == RA)
		data->keys.rotate_right = true;
	if (keycode == LA)
		data->keys.rotate_left = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->keys.up = false;
	if (keycode == S)
		data->keys.down = false;
	if (keycode == A)
		data->keys.left = false;
	if (keycode == D)
		data->keys.right = false;
	if (keycode == RA)
		data->keys.rotate_right = false;
	if (keycode == LA)
		data->keys.rotate_left = false;
	return (0);
}

void	set_door_state(t_data *data, bool closed, int move_x, int move_y)
{
	if (closed)
	{
		data->map->map[move_y][move_x] = 'U';
		data->door_flag = 1;
	}
	else
	{
		data->map->map[move_y][move_x] = 'D';
		data->door_flag = 30000;
	}
}

void	handel_door(t_data *data)
{
	int	move_x;
	int	move_y;

	move_x = (data->map->rx / data->map->pixel);
	move_y = (data->map->ry / data->map->pixel);
	if (data->r_angle >= 50 && data->r_angle < 130)
		move_y -= 1;
	else if (data->r_angle >= 130 && data->r_angle < 210)
		move_x -= 1;
	else if (data->r_angle >= 210 && data->r_angle < 290)
		move_y += 1;
	else
		move_x += 1;
	if (move_y >= 0 && move_x >= 0 && move_y < data->map->height
		&& move_x < (int)ft_strlen(data->map->map[move_y])
		&& data->map->map[move_y][move_x]
		&& data->map->map[move_y][move_x] != '1'
		&& data->map->map[move_y][move_x] != ' ')
	{
		if (data->map->map[move_y][move_x] == 'D')
			set_door_state(data, 1, move_x, move_y);
		else if (data->map->map[move_y][move_x] == 'U')
			set_door_state(data, 0, move_x, move_y);
	}
}
