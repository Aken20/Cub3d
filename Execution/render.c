/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:54:42 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/09/10 02:02:13 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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

void	draw_wall(t_data *data, bool is_vert, t_img *img)
{
	float	x;
	float	y;
	float	y_step;
	int		color;

	y = 0;
	color = 0;
	y_step = (float)img->height / data->line_height;
	if (is_vert)
		x = ((float)((int)data->vy % data->map->pixel)
				/ (data->map->pixel)) * img->width;
	else
		x = ((float)((int)data->hx % data->map->pixel)
				/ (data->map->pixel)) * img->width;
	while (data->start < data->end)
	{
		color = my_mlx_pixel_get(img, x, y);
		my_mlx_pixel_put(data->screen, data->x_screen, data->start++, color);
		y += y_step;
	}
}

static void	draw_screen(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(data->screen, x, y, data->map->ceiling);
			else
				my_mlx_pixel_put(data->screen, x, y, data->map->floor);
			x++;
		}
		x = 0;
		y++;
	}
	draw_ray(data);
}

int	ft_render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	draw_screen(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	return (0);
}
