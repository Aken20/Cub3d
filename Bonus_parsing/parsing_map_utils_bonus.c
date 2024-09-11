/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:47:53 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 04:20:27 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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
