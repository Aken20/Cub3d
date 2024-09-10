/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_va_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:22:12 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 21:22:55 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	free_2d(char ***ptr)
{
	int	j;

	if (ptr && *ptr)
	{
		j = 0;
		while ((*ptr)[j])
		{
			free((*ptr)[j]);
			j++;
		}
		if (*ptr)
			free(*ptr);
		*ptr = NULL;
	}
}

void	free_textures(t_map *map)
{
	if (!map)
		return ;
	free(map->north_txture);
	free(map->south_txture);
	free(map->east_txture);
	free(map->west_txture);
	free(map->floor_color);
	free(map->ceiling_color);
}

void	free_map_stuct(t_map *map)
{
	if (!map)
		return ;
	free_textures(map);
	free_2d(&map->map);
	free_2d(&map->file);
}

void	free_vars_stuct(t_vars *vars)
{
	if (!vars)
		return ;
	free(vars->line);
	free(vars->tmp);
	free_2d(&vars->splitted);
}
