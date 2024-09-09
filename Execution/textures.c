/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 07:27:49 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 01:54:47 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	open_textures(t_data *data)
{
	data->screen = malloc(sizeof(t_img));
	data->W_Wall = malloc(sizeof(t_img));
	data->E_Wall = malloc(sizeof(t_img));
	data->N_Wall = malloc(sizeof(t_img));
	data->S_Wall = malloc(sizeof(t_img));
	data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
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
	if (!data->W_Wall->img || !data->E_Wall->img
		|| !data->N_Wall->img || !data->S_Wall->img || !data->screen->img)
		exit_error("(Malloc failed)", data->map, NULL);
}

void	get_img_address(t_data *data)
{
	data->screen->addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bits_per_pixel, &data->screen->line_length,
			&data->screen->endian);
	data->E_Wall->addr = mlx_get_data_addr(data->E_Wall->img,
			&data->E_Wall->bits_per_pixel, &data->E_Wall->line_length,
			&data->E_Wall->endian);
	data->W_Wall->addr = mlx_get_data_addr(data->W_Wall->img,
			&data->W_Wall->bits_per_pixel, &data->W_Wall->line_length,
			&data->W_Wall->endian);
	data->N_Wall->addr = mlx_get_data_addr(data->N_Wall->img,
			&data->N_Wall->bits_per_pixel, &data->N_Wall->line_length,
			&data->N_Wall->endian);
	data->S_Wall->addr = mlx_get_data_addr(data->S_Wall->img,
			&data->S_Wall->bits_per_pixel, &data->S_Wall->line_length,
			&data->S_Wall->endian);
}
