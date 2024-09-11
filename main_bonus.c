/* ************************************************************************** */
/*														                    */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:08:07 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/09 06:08:12 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d_bonus.h"

void	ft_free_data(t_data *data)
{
	free(data->screen);
	free(data->mini_map);
	free(data->mini_map_frame);
	free(data->w_wall);
	free(data->e_wall);
	free(data->n_wall);
	free(data->s_wall);
	free(data->door[0]);
	free(data->door[1]);
	free(data->door[2]);
	free(data->flame[0]);
	free(data->flame[1]);
	free(data->flame[2]);
	mlx_destroy_window(data->mlx, data->win);
	free(data);
}

t_data	*ft_init(t_map *map)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->keys.up = false;
	data->keys.zoom_in = false;
	data->keys.zoom_out = false;
	data->keys.down = false;
	data->keys.left = false;
	data->keys.right = false;
	data->keys.rotate_left = false;
	data->keys.rotate_right = false;
	data->map = map;
	data->map->pixel = 800;
	data->mini_map_scale = 20;
	data->map->speed = 200;
	ft_player_find(data);
	get_width(data);
	data->width = data->map->width * 2;
	data->height = data->map->height * 2;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d");
	open_textures(data);
	data->door_flag = 0;
	data->flame_flag = 0;
	return (data);
}

void	extracting_the_map(t_map *map_data)
{
	t_vars	vars;

	getting_the_height(map_data);
	vars.x = -1;
	vars.y = -1;
	map_data->map = (char **)malloc(sizeof(char *) * (map_data->height + 1));
	if (!map_data->map)
		exit_error("(Malloc failed)", map_data, NULL);
	while (map_data->file[++vars.x])
	{
		if (map_data->file[vars.x][0] == '1'
			|| (map_data->file[vars.x][0] == ' ')
			|| map_data->file[vars.x][0] == '0')
		{
			vars.y++;
			map_data->map[vars.y] = ft_strdup(map_data->file[vars.x]);
		}
	}
	map_data->map[vars.y + 1] = NULL;
}

static void	parsing(t_map *map, t_vars *vars, char **av)
{
	init_struct(map, vars);
	check_map_extention(av[1]);
	reading_the_file(map, av[1]);
	check_white_spaces(map);
	check_unwanted_chars(map);
	defining_textures(map);
	parsing_textures(map);
	defining_colors(map);
	parsing_colors(map);
	extracting_the_map(map);
	parsing_the_map(map);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_map	map;
	t_vars	vars;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		exit(1);
	}
	parsing(&map, &vars, av);
	data = ft_init(&map);
	mlx_loop_hook(data->mlx, ft_render, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, ft_mouse_hocks, data);
	mlx_hook(data->win, 17, 1L << 0, ft_quit_game, data);
	mlx_loop(data->mlx);
	return (0);
}
