/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extra_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 04:17:20 by suibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 04:17:35 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	parsing_flame_textures(t_map *map_data)
{
	t_vars	vars;

	vars.fd = open("texture/flame_1.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid flame animation texture)", map_data, NULL);
	close(vars.fd);
	vars.fd = open("texture/flame_2.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid flame animation texture)", map_data, NULL);
	close(vars.fd);
	vars.fd = open("texture/flame_3.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid flame animation texture)", map_data, NULL);
	close(vars.fd);
	vars.fd = open("texture/mini_map_frame.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid map frame texture)", map_data, NULL);
	close(vars.fd);
}

void	parsing_door_textures(t_map *map_data)
{
	t_vars	vars;

	vars.fd = open("texture/door_1.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid door texture)", map_data, NULL);
	close(vars.fd);
	vars.fd = open("texture/door_2.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid door texture)", map_data, NULL);
	close(vars.fd);
	vars.fd = open("texture/door_3.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid door texture)", map_data, NULL);
	close(vars.fd);
	vars.fd = open("texture/door_4.xpm", O_RDONLY);
	if (vars.fd < 0)
		exit_error("(Invalid door texture)", map_data, NULL);
	close(vars.fd);
	parsing_flame_textures(map_data);
}
