/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 04:15:22 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 04:16:53 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3d_bonus.h"

void	parsing_textures(t_map *map_data)
{
	t_vars	vars;

	vars.fd = open(map_data->north_txture, O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid file descriptor north)", map_data, NULL);
	close(vars.fd);
	vars.fd = open(map_data->south_txture, O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid file descriptor south)", map_data, NULL);
	close(vars.fd);
	vars.fd = open(map_data->west_txture, O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid file descriptor west)", map_data, NULL);
	close(vars.fd);
	vars.fd = open(map_data->east_txture, O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid file descriptor east)", map_data, NULL);
	close(vars.fd);
	parsing_door_textures(map_data);
}

int	define_texture(char **splitted, t_map *map_data)
{
	if (ft_strncmp(splitted[0], "NO", 2) == 0)
	{
		return (map_data->north_txture = ft_strdup(splitted[1]), 1);
	}
	else if (ft_strncmp(splitted[0], "SO", 2) == 0)
	{
		return (map_data->south_txture = ft_strdup(splitted[1]), 1);
	}
	else if (ft_strncmp(splitted[0], "WE", 2) == 0)
	{
		return (map_data->west_txture = ft_strdup(splitted[1]), 1);
	}
	else if (ft_strncmp(splitted[0], "EA", 2) == 0)
	{
		return (map_data->east_txture = ft_strdup(splitted[1]), 1);
	}
	return (4);
}

void	check_duplicated_textures(t_map *map_data)
{
	t_vars	vars;

	vars.x = -1;
	vars.counter = 0;
	while (map_data->file[++vars.x])
	{
		if (map_data->file[vars.x][0] == 'N'
			|| map_data->file[vars.x][0] == 'S'
			|| map_data->file[vars.x][0] == 'W'
			|| map_data->file[vars.x][0] == 'E')
		{
			vars.splitted = ft_split(map_data->file[vars.x], ' ');
			if (!vars.splitted[0] || !vars.splitted[1])
				exit_error("(invalid texture)", map_data, NULL);
			vars.counter++;
			free_2d(&vars.splitted);
		}
		if (vars.counter > 4)
			exit_error("(found duplicated texture)", map_data, NULL);
	}
}

void	texture_check(t_map *map_data, char **splitted, int *txturecounter)
{
	if (ft_strcmp(splitted[0], "NO") == 0
		|| ft_strcmp(splitted[0], "SO") == 0
		|| ft_strcmp(splitted[0], "WE") == 0
		|| ft_strcmp(splitted[0], "EA") == 0)
	{
		*txturecounter += define_texture(splitted, map_data);
		free_2d(&splitted);
		splitted = NULL;
	}
	else if (ft_strcmp(splitted[0], "C") != 0
		&& ft_strcmp(splitted[0], "F") != 0)
		exit_error("(invalid texture data)", map_data, NULL);
	if (splitted)
	{
		free_2d(&splitted);
		splitted = NULL;
	}
}

void	defining_textures(t_map *map_data)
{
	t_vars	vars;

	check_duplicated_textures(map_data);
	vars.x = -1;
	vars.txturecounter = 0;
	vars.splitted = NULL;
	while (map_data->file[++vars.x] && vars.txturecounter != 4)
	{
		if (map_data->file[vars.x][0] == '1'
			|| map_data->file[vars.x][0] == '0')
			exit_error("(wrong map position or undefined character)",
				map_data, NULL);
		vars.splitted = ft_split(map_data->file[vars.x], ' ');
		if (vars.splitted && vars.splitted[0] && vars.splitted[1])
		{
			texture_check(map_data, vars.splitted, &vars.txturecounter);
		}
	}
	if (vars.txturecounter != 4)
		exit_error("(Invalid texture or no texture found)", map_data, NULL);
}
