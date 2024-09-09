/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:13:12 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/09 05:35:35 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

static void	ft_up(t_data *data)
{
	int	speed;
	int	move_x;
	int	move_y;

	speed = data->map->speed;
	move_x = (data->map->rx + cos(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	move_y = (data->map->ry - sin(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
		&& move_x < (int)ft_strlen(data->map->map[move_y])
		&& data->map->map[move_y][move_x]
		&& (data->map->map[move_y][move_x] == '0'
		|| data->map->map[move_y][move_x] == 'U') && speed--)
	{
		data->map->px += cos(d_to_r(data->map->angle));
		data->map->rx += cos(d_to_r(data->map->angle));
		data->map->py -= sin(d_to_r(data->map->angle));
		data->map->ry -= sin(d_to_r(data->map->angle));
		move_x = (data->map->rx + cos(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
		move_y = (data->map->ry - sin(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
	}
}

static void	ft_down(t_data *data)
{
	int	speed;
	int	move_x;
	int	move_y;

	speed = data->map->speed;
	move_x = (data->map->rx - cos(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	move_y = (data->map->ry + sin(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
		&& move_x < (int)ft_strlen(data->map->map[move_y])
		&& data->map->map[move_y][move_x]
		&& (data->map->map[move_y][move_x] == '0'
		|| data->map->map[move_y][move_x] == 'U') && speed--)
	{
		data->map->px -= cos(d_to_r(data->map->angle));
		data->map->rx -= cos(d_to_r(data->map->angle));
		data->map->py += sin(d_to_r(data->map->angle));
		data->map->ry += sin(d_to_r(data->map->angle));
		move_x = (data->map->rx - cos(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
		move_y = (data->map->ry + sin(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
	}
}

static void	ft_left(t_data *data)
{
	int	speed;
	int	move_x;
	int	move_y;

	speed = data->map->speed;
	move_x = (data->map->rx - sin(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	move_y = (data->map->ry - cos(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
		&& move_x < (int)ft_strlen(data->map->map[move_y])
		&& data->map->map[move_y][move_x]
		&& (data->map->map[move_y][move_x] == '0'
		|| data->map->map[move_y][move_x] == 'U') && speed--)
	{
		data->map->px -= sin(d_to_r(data->map->angle));
		data->map->rx -= sin(d_to_r(data->map->angle));
		data->map->py -= cos(d_to_r(data->map->angle));
		data->map->ry -= cos(d_to_r(data->map->angle));
		move_x = (data->map->rx - sin(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
		move_y = (data->map->ry - cos(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
	}
}

static void	ft_right(t_data *data)
{
	int	speed;
	int	move_x;
	int	move_y;

	speed = data->map->speed;
	move_x = (data->map->rx + sin(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	move_y = (data->map->ry + cos(d_to_r(data->map->angle))
			* (data->map->pixel / 1.5)) / data->map->pixel;
	while (move_y >= 0 && move_x >= 0 && move_y < data->map->height
		&& move_x < (int)ft_strlen(data->map->map[move_y])
		&& data->map->map[move_y][move_x]
		&& (data->map->map[move_y][move_x] == '0'
		|| data->map->map[move_y][move_x] == 'U') && speed--)
	{
		data->map->px += sin(d_to_r(data->map->angle));
		data->map->rx += sin(d_to_r(data->map->angle));
		data->map->py += cos(d_to_r(data->map->angle));
		data->map->ry += cos(d_to_r(data->map->angle));
		move_x = (data->map->rx + sin(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
		move_y = (data->map->ry + cos(d_to_r(data->map->angle))
				* (data->map->pixel / 1.5)) / data->map->pixel;
	}
}

void	ft_hocks(t_data *data)
{
	if (data->keys.up)
		ft_up(data);
	if (data->keys.down)
		ft_down(data);
	if (data->keys.left)
		ft_left(data);
	if (data->keys.right)
		ft_right(data);
	if (data->keys.rotate_right)
	{
		data->map->angle -= 3;
		if (data->map->angle < 0)
			data->map->angle += 360;
	}
	if (data->keys.rotate_left)
	{
		data->map->angle += 3;
		if (data->map->angle > 360)
			data->map->angle -= 360;
	}
}
