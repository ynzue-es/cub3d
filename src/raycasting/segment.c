/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/06 13:45:19 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int key_code(int key)
{
	if(key == 119)
	{
		float data->player_pos_x = data->player_pos_x + cos(data->player_angle) * 0.5;
    	float data->player_pos_y = data->player_pos_y + sin(data->player_angle) * 0.5;
	}
		
}
void	ray_cast(t_data_game *data_map,t_window *data_mlx,float angle,int player_x,int player_y)
{
	
	float ray_x = player_x * 32 + 16; 
    float ray_y = player_y * 32 + 16;
    int map_x;
	int map_y;
    float ray_dir_x = cos(angle);
    float ray_dir_y = sin(angle);
    int i;
	mlx_key_hook(data_mlx->window_ptr,key_code,data_map);
	i = 0;
	(void)data_map;
    while (1)
    {
        
        map_x = (int)(ray_x / 32);
        map_y = (int)(ray_y / 32);
        if (data_map->map_data.map[map_y][map_x] == '1')
           break;
        mlx_pixel_put(data_mlx->mlx_ptr, data_mlx->window_ptr, (int)ray_x + i, (int)ray_y, 0xFF0000); 
        ray_x += ray_dir_x * 0.5;
        ray_y += ray_dir_y * 0.5;
    }
}

int	put_segment(t_window *data_mlx,t_data_game *data_map)
{
	int i;
	int j;
	int x;
	int y;
	
	int player_pos_x;
	int player_pos_y;
	// t_segment segment;
	// segment.p1.x = 100;
	// segment.p1.y = 500;
	// segment.p2.x = 2000;
	// segment.p2.y = 300;
	
	// int p1 = segment.p2.x - segment.p1.x;
	// int p2 = segment.p2.y - segment.p1.y;
	// int longeur = p1 + p2 - 1000;

	j = 0;
	i = 0;
	x = 0;
	y = 0;
	
	while(data_map->map_data.map[i])
	{
		j = 0;
		while(data_map->map_data.map[i][j])
		{
			y = 0;
			if(data_map->map_data.map[i][j] == '1')
			{
				while(y < 32)
				{
					x = 0;
					while(x < 32)
					{
						mlx_pixel_put(data_mlx->mlx_ptr,data_mlx->window_ptr,j * 32 + x, i * 32 + y,0xFFFFFF);
						x++;
					}
					y++;
				}
			}
			if(data_map->map_data.map[i][j] == '0')
			{
				y = 0;
				while(y < 32)
				{
					x = 0;
					while(x < 32)
					{
						mlx_pixel_put(data_mlx->mlx_ptr,data_mlx->window_ptr,j * 32 + x,i * 32 + y,0xF0FF00);
						x++;
					}
					y++;
				}
			}
			if(data_map->map_data.map[i][j] == 'N')
			{
				y = 0;
				while(y < 32)
				{
					x = 0;
					while(x < 32)
					{
						mlx_pixel_put(data_mlx->mlx_ptr,data_mlx->window_ptr,j * 32 + x, i * 32 + y,0x000066);
						x++;
					}
					y++;
				}
				player_pos_x = j;
				player_pos_y = i;
			}
			j++;
		}
		i++;
	}

	float fov = M_PI / 3;  
    int num_rays = 200;    
 
	i = 0;

    while(i < num_rays)
    {
        
        float ray_angle = 3 * M_PI / 2 - fov/ 2 + (fov * i / num_rays);
        ray_cast(data_map,data_mlx, ray_angle, player_pos_x, player_pos_y);
		i++;
    }
	return (0);
}