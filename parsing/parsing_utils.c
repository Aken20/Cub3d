/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 04:30:17 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 04:04:57 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	getting_the_height(t_map *map_data)
{
	t_vars	vars;

	vars.x = -1;
	vars.y = -1;
	map_data->width = 0;
	map_data->height = 0;
	while (map_data->file[++vars.x])
	{
		if (map_data->file[vars.x][0] == '1'
			|| map_data->file[vars.x][0] == ' ')
			map_data->height++;
	}
}

void	exit_error(char *str, t_map *map, t_vars *vars)
{
	free_map_stuct(map);
	free_vars_stuct(vars);
	ft_printf("Error\n%s\n", str);
	exit(1);
}

int	find_char_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	valid_view_char(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (0);
	return (1);
}
