/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:09:04 by yannis            #+#    #+#             */
/*   Updated: 2025/08/23 14:53:46 by yannis           ###   ########.fr       */
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

void draw_background(t_data_pixel *data_pixel)
{
	int y;
	int x;
	int color;

	y = 0;
    while (y < 1090)
    {
        color = (y < 545) ? 0x87CEEB : 0x228B22;
		x = 0;
        while (x < 2000)
		{
            my_mlx_pixel_put(data_pixel, x, y, color);
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
	
	vx = data_game->ray_data.ray_x - (data_game->player_pos.player_pos_x * 16 + 8);
	vy = data_game->ray_data.ray_y - (data_game->player_pos.player_pos_y * 16 + 8);
	dist = sqrtf(pow(vx, 2) + pow(vy, 2));
	dist = dist * cos(ray_angle - data_game->player_pos.player_angle);
	proj_plane = (1090 / 2.0f) / tanf((60.0f * (M_PI/180.0f)) / 2.0f);
	wall_height = (16 * proj_plane) / dist;
	draw_start = (1090 / 2) - (wall_height / 2);
	draw_end = (1090 / 2) + (wall_height / 2);
	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(&data_game->data_pixel, i, y, 0xFF0000);
		y++;
	}
	return (0);
}