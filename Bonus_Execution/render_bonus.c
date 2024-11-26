/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 05:36:37 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/09 23:08:04 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	color = 0;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (color);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = (*(unsigned int *)dst);
	return (color);
}

void	ft_draw_cursor(t_data *data)
{
	float	y;
	float	x;
	int		i;

	y = 0;
	x = 0;
	i = 0;
	while (i < data->mini_map_scale)
	{
		my_mlx_pixel_put(data->mini_map, 100 + x, 100 + y, 0xa9b5fa);
		x += cos(d_to_r(data->map->angle));
		y -= sin(d_to_r(data->map->angle));
		i++;
	}
}

void	ft_draw_player(t_data *data)
{
	int	y;
	int	x;

	x = 100 - (data->mini_map_scale / 2);
	y = 100 - (data->mini_map_scale / 2);
	while (y < (100 + (data->mini_map_scale / 2)))
	{
		while (x < (100 + (data->mini_map_scale / 2)))
		{
			my_mlx_pixel_put(data->mini_map, x, y, 0x0000fa);
			x++;
		}
		x = 100 - (data->mini_map_scale / 2);
		y++;
	}
	ft_draw_cursor(data);
}

int	ft_render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ft_hocks(data);
	draw_screen(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->mini_map->img,
		WIDTH - 220, HEIGHT - 220);
	if (SP == 49)
		mlx_put_image_to_window(data->mlx, data->win, data->mini_map_frame->img,
			WIDTH - 240, HEIGHT - 240);
	return (0);
}
