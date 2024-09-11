/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 04:23:00 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 08:05:06 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

int	valid_surrounding_char(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != 'D'
		&& c != 'U' && c != '1' && c != '0' && c != 'F')
		return (0);
	return (1);
}

void	parse_view(t_map *map_data)
{
	t_vars	vars;

	vars.y = -1;
	while (map_data->map[++vars.y])
	{
		vars.x = -1;
		while (map_data->map[vars.y][++vars.x])
		{
			if (valid_view_char(map_data->map[vars.y][vars.x]))
			{
				if (vars.y == 0 || vars.x == 0
					|| vars.y == map_data->height - 1
					|| vars.x > (int)ft_strlen(map_data->map[vars.y - 1])
					|| vars.x > (int)ft_strlen(map_data->map[vars.y + 1]))
					exit_error("(Invalid view position)", map_data, NULL);
				if (!valid_surrounding_char(map_data->map[vars.y - 1][vars.x])
					||!valid_surrounding_char(map_data->map[vars.y + 1][vars.x])
					||!valid_surrounding_char(map_data->map[vars.y][vars.x - 1])
					||!valid_surrounding_char(map_data->map[vars.y][vars.x + 1])
					)
					exit_error("(Invalid view position)", map_data, NULL);
			}
		}
	}
}

void	check_duplicated_view_char(t_map *m_data)
{
	t_vars	v;

	v.y = -1;
	v.isviewfound = 0;
	while (m_data->map[++v.y])
	{
		v.x = -1;
		while (m_data->map[v.y][++v.x])
		{
			if (m_data->map[v.y][v.x] == 'N' || m_data->map[v.y][v.x] == 'S'
				|| m_data->map[v.y][v.x] == 'W' || m_data->map[v.y][v.x] == 'E')
			{
				v.isviewfound++;
				if (v.isviewfound > 1)
					exit_error("(Found duplicated view)", m_data, NULL);
			}
			else if (!valid_surrounding_char(m_data->map[v.y][v.x])
					&& m_data->map[v.y][v.x] != ' ')
				exit_error("(undefined character)", m_data, NULL);
		}
	}
	if (v.isviewfound != 1)
		exit_error("(No view found)", m_data, NULL);
}

void	check_surrounding(t_map *map_data, char c)
{
	t_vars	vars;

	vars.y = -1;
	while (map_data->map[++vars.y])
	{
		vars.x = -1;
		while (map_data->map[vars.y][++vars.x])
		{
			if (map_data->map[vars.y][vars.x] == c)
			{
				if (vars.y == 0 || vars.x == 0
					|| vars.y == map_data->height - 1)
					exit_error("(Invalid map)", map_data, NULL);
				if (vars.x > (int)ft_strlen(map_data->map[vars.y - 1])
					|| vars.x > (int)ft_strlen(map_data->map[vars.y + 1]))
					exit_error("(Invalid map)", map_data, NULL);
				if (!valid_surrounding_char(map_data->map[vars.y - 1][vars.x])
					||!valid_surrounding_char(map_data->map[vars.y + 1][vars.x])
					||!valid_surrounding_char(map_data->map[vars.y][vars.x - 1])
					||!valid_surrounding_char(map_data->map[vars.y][vars.x + 1])
					)
					exit_error("(Invalid map)", map_data, NULL);
			}
		}
	}
}

void	parsing_the_map(t_map *map_data)
{
	check_surrounding(map_data, '0');
	check_surrounding(map_data, 'D');
	check_surrounding(map_data, 'U');
	check_surrounding(map_data, 'F');
	check_duplicated_view_char(map_data);
	parse_view(map_data);
}
