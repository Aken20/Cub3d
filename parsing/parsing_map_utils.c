/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:47:53 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 23:42:59 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	valid_line_char(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != 'D'
		&& c != 'U' && c != '1' && c != '0' && c != 'F' && c != ' ')
		return (0);
	return (1);
}

bool	check_line_value(char *line, t_vars *vars)
{
	static int	i;
	int			k;

	vars->j = 0;
	if (i == 0)
	{
		vars->len = 0;
		i++;
	}
	if (ft_strnstr(line, "NO ", 3)
		|| ft_strnstr(line, "SO ", 3) || ft_strnstr(line, "WE ", 3)
		|| ft_strnstr(line, "EA ", 3) || ft_strnstr(line, "S ", 2)
		|| ft_strnstr(line, "F ", 2) || ft_strnstr(line, "C ", 2))
		vars->len++;
	else if (vars->len == 6)
	{
		k = -1;
		while (line[++k] && valid_line_char(line[k]))
			vars->len++;
	}
	else if (vars->len >= 7 && line && line[0] == '\n')
		return (false);
	return (true);
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
			else if (m_data->map[v.y][v.x] != '0'
				&& m_data->map[v.y][v.x] != '1'
				&& m_data->map[v.y][v.x] != ' ')
				exit_error("(undefined character)", m_data, NULL);
		}
	}
	if (v.isviewfound != 1)
		exit_error("(No view found)", m_data, NULL);
}
