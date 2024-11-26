/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:47:53 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 23:55:45 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

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
