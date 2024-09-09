/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:36:37 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/09 06:35:29 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

int	ft_quit_game(t_data *data)
{
	ft_free_data(data);
	exit(0);
}

bool	is_in_range(float px, float py)
{
	float	distance;

	distance = sqrt(pow(100 - px, 2) + pow(100 - py, 2));
	if (distance <= 100)
		return (1);
	return (0);
}

void	draw_minimap_charecter(t_data *data, int x, int m_x, int m_y)
{
	int	y;

	y = ((data->map->ry / data->map->pixel) * data->mini_map_scale) - 100;
	if (is_in_range(m_x, m_y))
	{
		my_mlx_pixel_put(data->mini_map, m_x, m_y, 0x6a592b);
		if ((m_y + y) / data->mini_map_scale < 0 || (m_y + y)
			/ data->mini_map_scale >= data->map->height
			|| (m_x + x) / data->mini_map_scale < 0
			|| (m_x + x) / data->mini_map_scale >= (int)ft_strlen(
				data->map->map[(m_y + y) / data->mini_map_scale])
			|| data->map->map[(m_y + y) / data->mini_map_scale]
			[(m_x + x) / data->mini_map_scale] == ' ')
			my_mlx_pixel_put(data->mini_map, m_x, m_y, 0x0000fa);
		else if ((data->map->map[(m_y + y) / data->mini_map_scale]
				[(m_x + x) / data->mini_map_scale] == '1'
				|| data->map->map[(m_y + y) / data->mini_map_scale]
				[(m_x + x) / data->mini_map_scale] == 'D'
				|| data->map->map[(m_y + y) / data->mini_map_scale]
				[(m_x + x) / data->mini_map_scale] == 'F'))
			my_mlx_pixel_put(data->mini_map, m_x, m_y, 0x00ff00);
	}
	else
		my_mlx_pixel_put(data->mini_map, m_x, m_y, -1);
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	m_x;
	int	m_y;

	x = ((data->map->rx / data->map->pixel) * data->mini_map_scale) - 100;
	y = ((data->map->ry / data->map->pixel) * data->mini_map_scale) - 100;
	m_x = 0;
	m_y = 0;
	while (m_y < 200)
	{
		while (m_x < 200)
		{
			draw_minimap_charecter(data, x, m_x, m_y);
			m_x++;
		}
		m_x = 0;
		m_y++;
	}
	ft_draw_player(data);
}

void	draw_screen(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(data->screen, x, y, data->map->ceiling);
			else
				my_mlx_pixel_put(data->screen, x, y, data->map->floor);
			x++;
		}
		x = 0;
		y++;
	}
	draw_ray(data);
}
