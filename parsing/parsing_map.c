/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:23:05 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 22:55:37 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static void	check_view_positions(t_map *map_data, int y, int x)
{
	if (y == 0 || x == 0 || y == map_data->height - 1)
		exit_error("(Invalid view position)", map_data, NULL);
	if (x > (int)ft_strlen(map_data->map[y - 1])
		|| x > (int)ft_strlen(map_data->map[y + 1]))
		exit_error("(Invalid view position)", map_data, NULL);
	if ((map_data->map[y - 1][x] != '1' && map_data->map[y - 1][x] != '0')
		|| (map_data->map[y + 1][x] != '1' && map_data->map[y + 1][x] != '0')
		|| (map_data->map[y][x - 1] != '1' && map_data->map[y][x - 1] != '0')
		|| (map_data->map[y][x + 1] != '1' && map_data->map[y][x + 1] != '0'))
		exit_error("(Invalid view position)", map_data, NULL);
}


void	parse_view(t_map *map_data)
{
	t_vars	vars;

	init_vars(&vars);
	vars.y = -1;
	while (map_data->map[++vars.y])
	{
		vars.x = -1;
		while (map_data->map[vars.y][++vars.x])
		{
			if (map_data->map[vars.y][vars.x] == 'N'
				|| map_data->map[vars.y][vars.x] == 'S'
				|| map_data->map[vars.y][vars.x] == 'W'
				|| map_data->map[vars.y][vars.x] == 'E')
			{
				check_view_positions(map_data, vars.y, vars.x);
			}
		}
	}
}

void	check_surrounding_pos(t_map *map_data, int x, int y)
{
	if (y == 0 || x == 0 || y == map_data->height - 1)
		exit_error("(Invalid map)", map_data, NULL);
	if (x > (int)ft_strlen(map_data->map[y - 1])
		|| x > (int)ft_strlen(map_data->map[y + 1]))
		exit_error("(Invalid map)", map_data, NULL);
	if ((map_data->map[y - 1][x] != '1' && map_data->map[y - 1][x] != '0'
		&& !valid_view_char(map_data->map[y - 1][x]))
		|| (map_data->map[y + 1][x] != '1' && map_data->map[y + 1][x] != '0'
		&& !valid_view_char(map_data->map[y + 1][x]))
		|| (map_data->map[y][x - 1] != '1' && map_data->map[y][x - 1] != '0'
		&& !valid_view_char(map_data->map[y][x - 1]))
		|| (map_data->map[y][x + 1] != '1' && map_data->map[y][x + 1] != '0'
		&& !valid_view_char(map_data->map[y][x + 1])))
		exit_error("(Invalid map)", map_data, NULL);
}

void	check_surrounding(t_map *map_data)
{
	t_vars	vars;

	vars.x = -1;
	vars.y = -1;
	while (map_data->map[++vars.y])
	{
		vars.x = -1;
		while (map_data->map[vars.y][++vars.x])
		{
			if (map_data->map[vars.y][vars.x] == '0')
				check_surrounding_pos(map_data, vars.x, vars.y);
		}
	}
}

void	parsing_the_map(t_map *map_data)
{
	check_surrounding(map_data);
	check_duplicated_view_char(map_data);
	parse_view(map_data);
}
