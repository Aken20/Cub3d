/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 06:22:46 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 03:26:38 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

void	alloc_textures(t_data *data)
{
	data->screen = malloc(sizeof(t_img));
	data->mini_map = malloc(sizeof(t_img));
	data->mini_map_frame = malloc(sizeof(t_img));
	data->door[0] = malloc(sizeof(t_img));
	data->door[1] = malloc(sizeof(t_img));
	data->door[2] = malloc(sizeof(t_img));
	data->flame[0] = malloc(sizeof(t_img));
	data->flame[1] = malloc(sizeof(t_img));
	data->flame[2] = malloc(sizeof(t_img));
	data->W_Wall = malloc(sizeof(t_img));
	data->E_Wall = malloc(sizeof(t_img));
	data->N_Wall = malloc(sizeof(t_img));
	data->S_Wall = malloc(sizeof(t_img));
	if (!data->W_Wall || !data->E_Wall || !data->N_Wall || !data->S_Wall
		|| !data->screen || !data->door[0] || !data->door[1] || !data->door[2]
		|| !data->flame[0] || !data->flame[1]
		|| !data->flame[2] || !data->mini_map_frame)
		exit_error("(Malloc failed)", data->map, NULL);
}

void	get_img_address_helper(t_data *data)
{
	data->screen->addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bits_per_pixel,
			&data->screen->line_length, &data->screen->endian);
	data->mini_map->addr = mlx_get_data_addr(data->mini_map->img,
			&data->mini_map->bits_per_pixel,
			&data->mini_map->line_length, &data->mini_map->endian);
	data->mini_map_frame->addr = mlx_get_data_addr(data->mini_map_frame->img,
			&data->mini_map_frame->bits_per_pixel,
			&data->mini_map_frame->line_length, &data->mini_map_frame->endian);
	data->E_Wall->addr = mlx_get_data_addr(data->E_Wall->img,
			&data->E_Wall->bits_per_pixel,
			&data->E_Wall->line_length, &data->E_Wall->endian);
	data->W_Wall->addr = mlx_get_data_addr(data->W_Wall->img,
			&data->W_Wall->bits_per_pixel,
			&data->W_Wall->line_length, &data->W_Wall->endian);
	data->N_Wall->addr = mlx_get_data_addr(data->N_Wall->img,
			&data->N_Wall->bits_per_pixel,
			&data->N_Wall->line_length, &data->N_Wall->endian);
	data->S_Wall->addr = mlx_get_data_addr(data->S_Wall->img,
			&data->S_Wall->bits_per_pixel,
			&data->S_Wall->line_length, &data->S_Wall->endian);
}

void	get_img_address(t_data *data)
{
	data->door[0]->addr = mlx_get_data_addr(data->door[0]->img,
			&data->door[0]->bits_per_pixel,
			&data->door[0]->line_length, &data->door[0]->endian);
	data->door[1]->addr = mlx_get_data_addr(data->door[1]->img,
			&data->door[1]->bits_per_pixel,
			&data->door[1]->line_length, &data->door[1]->endian);
	data->door[2]->addr = mlx_get_data_addr(data->door[2]->img,
			&data->door[2]->bits_per_pixel,
			&data->door[2]->line_length, &data->door[2]->endian);
	data->flame[0]->addr = mlx_get_data_addr(data->flame[0]->img,
			&data->flame[0]->bits_per_pixel,
			&data->flame[0]->line_length, &data->flame[0]->endian);
	data->flame[1]->addr = mlx_get_data_addr(data->flame[1]->img,
			&data->flame[1]->bits_per_pixel,
			&data->flame[1]->line_length, &data->flame[1]->endian);
	data->flame[2]->addr = mlx_get_data_addr(data->flame[2]->img,
			&data->flame[2]->bits_per_pixel,
			&data->flame[2]->line_length, &data->flame[2]->endian);
	get_img_address_helper(data);
}

void	open_textures_helper(t_data *data)
{
	data->W_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->west_txture,
			&(data->W_Wall->width), &(data->W_Wall->height));
	data->E_Wall->img = mlx_xpm_file_to_image(data->mlx, data->map->east_txture,
			&(data->E_Wall->width), &(data->E_Wall->height));
	data->N_Wall->img = mlx_xpm_file_to_image(data->mlx,
			data->map->north_txture, &(data->N_Wall->width),
			&(data->N_Wall->height));
	data->S_Wall->img = mlx_xpm_file_to_image(data->mlx,
			data->map->south_txture, &(data->S_Wall->width),
			&(data->S_Wall->height));
	if (!data->W_Wall->img || !data->E_Wall->img || !data->N_Wall->img
		|| !data->S_Wall->img || !data->screen->img
		|| !data->door[0]->img || !data->door[1]->img || !data->door[2]->img
		|| !data->flame[0]->img
		|| !data->flame[1]->img || !data->flame[2]->img
		|| !data->mini_map_frame->img)
		exit_error("(opening textures failed)", data->map, NULL);
	get_img_address(data);
}

void	open_textures(t_data *data)
{
	alloc_textures(data);
	data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->mini_map->img = mlx_new_image(data->mlx, 200, 200);
	data->mini_map_frame->img = mlx_xpm_file_to_image(data->mlx,
			"texture/mini_map_frame.xpm", &(data->door[0]->width),
			&(data->door[0]->height));
	data->door[0]->img = mlx_xpm_file_to_image(data->mlx,
			"texture/doorsblue1.xpm",
			&(data->door[0]->width), &(data->door[0]->height));
	data->door[1]->img = mlx_xpm_file_to_image(data->mlx,
			"texture/doorsblue2.xpm",
			&(data->door[1]->width), &(data->door[1]->height));
	data->door[2]->img = mlx_xpm_file_to_image(data->mlx,
			"texture/doorsblue3.xpm",
			&(data->door[2]->width), &(data->door[2]->height));
	data->flame[0]->img = mlx_xpm_file_to_image(data->mlx,
			"texture/flame_1.xpm", &(data->flame[0]->width),
			&(data->flame[0]->height));
	data->flame[1]->img = mlx_xpm_file_to_image(data->mlx,
			"texture/flame_2.xpm", &(data->flame[1]->width),
			&(data->flame[1]->height));
	data->flame[2]->img = mlx_xpm_file_to_image(data->mlx,
			"texture/flame_3.xpm", &(data->flame[2]->width),
			&(data->flame[2]->height));
	open_textures_helper(data);
}
