/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:14:16 by yannis            #+#    #+#             */
/*   Updated: 2025/08/23 14:14:29 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ray_minimap(t_data_game *data, float ray_angle,t_data_pixel *data_pixel)
{
	data->ray_data.ray_x = data->player_pos.player_pos_x * 16 + 8;
	data->ray_data.ray_y = data->player_pos.player_pos_y * 16 + 8;
	
	data->ray_data.ray_dir_x =  cos(ray_angle);
	data->ray_data.ray_dir_y =  sin(ray_angle);
	(void)data_pixel;
	while (1)
	{
		data->ray_data.map_x = (int)(data->ray_data.ray_x / 16);
		data->ray_data.map_y = (int)(data->ray_data.ray_y / 16);
		
		if (data->map_data.map[data->ray_data.map_y][data->ray_data.map_x] == '1')
			break ;
		my_mlx_pixel_put(data_pixel,(int)data->ray_data.ray_x,(int)data->ray_data.ray_y,0xFF0000);
		data->ray_data.ray_x += data->ray_data.ray_dir_x * 1;
		data->ray_data.ray_y += data->ray_data.ray_dir_y * 1;
	}
}

void display_minimap(t_data_game *data_game,t_data_pixel *data_pixel)
{
	int i;
	int j;
	int x;
	int y;

	j = 0;
	i = 0;
	x = 0;
	y = 0;
	while (data_game->map_data.map[i])
	{
		j = 0;
		while (data_game->map_data.map[i][j])
		{
			y = 0;
			if (data_game->map_data.map[i][j] == '1')
			{
				while (y < 16)
				{
					x = 0;
					while (x < 16)
					{
						
						my_mlx_pixel_put(data_pixel,j * 16 + x,i *16 + y,0xFFFFFF);
						x++;
					}
					y++;
				}
			}
			if (data_game->map_data.map[i][j] == '0')
			{
				y = 0;
				while (y < 16)
				{
					x = 0;
					while (x < 16)
					{
						my_mlx_pixel_put(data_pixel,j * 16 + x,i *16 + y,0xF00FFF);
						x++;
					}
					y++;
				}
			}
			j++;
		}
		i++;
	}
	while (y < 16)
    {
        x = 0;
        while (x < 16)
        {
			my_mlx_pixel_put(data_pixel,(int)(data_game->player_pos.player_pos_x * 16) + x,(int)(data_game->player_pos.player_pos_y * 16) + y, 0x000066);
            x++;
        }
        y++;
    }
}