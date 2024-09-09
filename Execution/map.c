/* ************************************************************************** */
/*                                              */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:54:32 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 01:54:33 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	ft_quit_game(t_data *data)
{
	ft_free_data(data);
	exit(0);
}

void	get_width(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->map[i])
	{
		if (data->map->width < (int)ft_strlen(data->map->map[i]))
			data->map->width = (int)ft_strlen(data->map->map[i]);
		i++;
	}
}

void	ft_player_find(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
		{
			if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S'
				|| data->map->map[i][j] == 'W' || data->map->map[i][j] == 'E')
			{
				data->map->px = (j * data->map->pixel) + (data->map->pixel / 3);
				data->map->py = (i * data->map->pixel) + (data->map->pixel / 3);
				if (data->map->map[i][j] == 'N')
					data->map->angle = 90;
				else if (data->map->map[i][j] == 'W')
					data->map->angle = 180;
				else if (data->map->map[i][j] == 'S')
					data->map->angle = 270;
				else if (data->map->map[i][j] == 'E')
					data->map->angle = 0;
			}
		}
	}
}
