/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:09:04 by yannis            #+#    #+#             */
/*   Updated: 2025/08/23 15:15:17 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	my_mlx_pixel_put(t_data_pixel *data_pixel, int x, int y, int color)
{ 
	char	*dst;
	if (x < 0 || y < 0 || x >= 2000 || y >= 1090)
		return ;
	dst = data_pixel->addr + (y * data_pixel->line_length + x * (data_pixel->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_background(t_data_game *data_game)
{
	int y;
	int x;
	int color;

	y = 0;
    while (y < data_game->data_mlx.height)
    {
		if (y < (data_game->data_mlx.height / 2))
        	color = 0x87CEEB;
		else
			color = 0x228B22;
		x = 0;
        while (x < data_game->data_mlx.width)
		{
            my_mlx_pixel_put(&data_game->data_pixel, x, y, color);
			x++;
		}
		y++;
    }
}

int	put_wall_segement(t_data_game *data_game, int i, float ray_angle)
{
	int y;
	float vx;
	float vy;
	float dist;
	int wall_height;
	int draw_start;
	int draw_end;
	float proj_plane;
	
	vx = data_game->ray_data.ray_x - (data_game->player_pos.player_pos_x * data_game->tile_size);
	vy = data_game->ray_data.ray_y - (data_game->player_pos.player_pos_y * data_game->tile_size);
	dist = sqrtf(pow(vx, 2) + pow(vy, 2));
	dist = dist * cos(ray_angle - data_game->player_pos.player_angle);
	proj_plane = (data_game->data_mlx.height / 2) / tanf((60 * (M_PI/180)) / 2);
	wall_height = (data_game->tile_size * proj_plane) / dist;
	draw_start = (data_game->data_mlx.height / 2) - (wall_height / 2);
	draw_end = (data_game->data_mlx.height / 2) + (wall_height / 2);
	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(&data_game->data_pixel, i, y, 0xFF0000);
		y++;
	}
	return (0);
}
