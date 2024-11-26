/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 07:27:49 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/11 08:10:34 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	open_textures(t_data *data)
{
	data->screen = malloc(sizeof(t_img));
	data->w_wall = malloc(sizeof(t_img));
	data->e_wall = malloc(sizeof(t_img));
	data->n_wall = malloc(sizeof(t_img));
	data->s_wall = malloc(sizeof(t_img));
	data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->w_wall->img = mlx_xpm_file_to_image(data->mlx, data->map->west_txture,
			&(data->w_wall->width), &(data->w_wall->height));
	data->e_wall->img = mlx_xpm_file_to_image(data->mlx, data->map->east_txture,
			&(data->e_wall->width), &(data->e_wall->height));
	data->n_wall->img = mlx_xpm_file_to_image(data->mlx,
			data->map->north_txture, &(data->n_wall->width),
			&(data->n_wall->height));
	data->s_wall->img = mlx_xpm_file_to_image(data->mlx,
			data->map->south_txture, &(data->s_wall->width),
			&(data->s_wall->height));
	if (!data->w_wall->img || !data->e_wall->img
		|| !data->n_wall->img || !data->s_wall->img || !data->screen->img)
		exit_error("(Malloc failed)", data->map, NULL);
}

void	get_img_address(t_data *data)
{
	data->screen->addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bits_per_pixel, &data->screen->line_length,
			&data->screen->endian);
	data->e_wall->addr = mlx_get_data_addr(data->e_wall->img,
			&data->e_wall->bits_per_pixel, &data->e_wall->line_length,
			&data->e_wall->endian);
	data->w_wall->addr = mlx_get_data_addr(data->w_wall->img,
			&data->w_wall->bits_per_pixel, &data->w_wall->line_length,
			&data->w_wall->endian);
	data->n_wall->addr = mlx_get_data_addr(data->n_wall->img,
			&data->n_wall->bits_per_pixel, &data->n_wall->line_length,
			&data->n_wall->endian);
	data->s_wall->addr = mlx_get_data_addr(data->s_wall->img,
			&data->s_wall->bits_per_pixel, &data->s_wall->line_length,
			&data->s_wall->endian);
}
