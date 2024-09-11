/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_file_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 04:01:20 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 23:26:51 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_vars(t_vars *vars)
{
	vars->line = NULL;
	vars->tmp = NULL;
	vars->splitted = NULL;
}

void	init_struct(t_map *map, t_vars *vars)
{
	map->map = NULL;
	map->file = NULL;
	map->south_txture = NULL;
	map->north_txture = NULL;
	map->east_txture = NULL;
	map->west_txture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
	vars->l = 0;
	vars->m = 0;
	vars->n = 0;
	vars->line = NULL;
	vars->tmp = NULL;
	vars->splitted = NULL;
}

void	check_map_extention(char *map_file)
{
	int	i;

	i = 0;
	if (!map_file)
		exit_error("(No file name found)", NULL, NULL);
	while (map_file[i])
		i++;
	if (map_file[i - 5] == '/' || i == 4)
		exit_error("(No file name found)", NULL, NULL);
	if (ft_strncmp(&map_file[i - 4], ".cub", 4) != 0)
		exit_error("(Invalid file extension)", NULL, NULL);
}

void	fill_the_file(t_map *map_data, int len, char *map_file)
{
	t_vars	vars;

	vars.fd = open(map_file, O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid file descriptor)", map_data, NULL);
	map_data->file = (char **)malloc(sizeof(char *) * (len + 1));
	if (!map_data->file)
		exit_error("(Malloc failed)", map_data, NULL);
	vars.line = get_next_line(vars.fd);
	if (vars.line == NULL)
		exit_error("(empty map !!)", NULL, NULL);
	vars.i = 0;
	while (vars.line)
	{
		vars.j = 0;
		if (!check_line_value(vars.line, &vars))
			break ;
		while (vars.line[vars.j] && vars.line[vars.j] != '\n')
			vars.j++;
		if (vars.j != 0)
			map_data->file[vars.i++] = ft_substr(vars.line, 0, vars.j);
		free(vars.line);
		vars.line = get_next_line(vars.fd);
	}
	map_data->file[vars.i] = NULL;
	close(vars.fd);
}

void	reading_the_file(t_map *map_data, char *map_file)
{
	t_vars	vars;

	init_struct(map_data, &vars);
	vars.fd = open(map_file, O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid file descriptor)", NULL, NULL);
	vars.line = get_next_line(vars.fd);
	if (vars.line == NULL)
		exit_error("(empty map !!!)", NULL, NULL);
	vars.i = 0;
	while (vars.line)
	{
		vars.i++;
		free(vars.line);
		vars.line = get_next_line(vars.fd);
	}
	if (vars.line)
	{
		free(vars.line);
		vars.line = NULL;
	}
	if (vars.line)
		free(vars.line);
	close(vars.fd);
	fill_the_file(map_data, vars.i, map_file);
}
