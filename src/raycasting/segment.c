/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/08 13:23:12 by engiusep         ###   ########.fr       */
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
int	key_code(int key, t_data_game *data)
{
	float new_x;
	float new_y;
	if (key == 119)
	{
		new_x = data->player_pos.player_pos_x + cos(data->player_pos.player_angle) * 0.5;
		new_y = data->player_pos.player_pos_y + sin(data->player_pos.player_angle) * 0.5;
		if(data->map_data.map[(int)new_y][(int)new_x] != '1')
		{
			data->player_pos.player_pos_x = new_x;
            data->player_pos.player_pos_y = new_y;
			
		}
	}
	else if(key == 115)
	{
		new_x = data->player_pos.player_pos_x + cos(data->player_pos.player_angle) * -0.5;
		new_y = data->player_pos.player_pos_y + sin(data->player_pos.player_angle) * -0.5;
		if(data->map_data.map[(int)new_y][(int)new_x] != '1')
		{
			data->player_pos.player_pos_x = new_x;
            data->player_pos.player_pos_y = new_y;
		}
	}
	else if (key == 100)
		data->player_pos.player_angle += 0.1;
	else if (key == 97)
		data->player_pos.player_angle -= 0.1;
		
	//printf("%f\n%f",data->player_pos.player_pos_x + cos(data->player_pos.player_angle) * 0.5,data->player_pos.player_pos_y + sin(data->player_pos.player_angle) * 0.5);
	
	mlx_clear_window(data->data_mlx->mlx_ptr,data->data_mlx->window_ptr);
	put_segment(data->data_mlx, data,data->data_pixel);
	//mlx_put_image_to_window(data->data_mlx->mlx_ptr,data->data_mlx->window_ptr,data->data_pixel->img_ptr,0,0);
	printf("key code = %d\n", key);
	return (0);
}

void	ray_cast(t_data_game *data, t_window *data_mlx, float ray_angle,t_data_pixel *data_pixel)
{
	float	ray_x;
	float	ray_y;
	int		map_x;
	int		map_y;
	float	ray_dir_x;
	float	ray_dir_y;
	int		i;

	(void)data_mlx;
	ray_x = data->player_pos.player_pos_x * 32 + 16;
	ray_y = data->player_pos.player_pos_y * 32 + 16;
	ray_dir_x =  cos(ray_angle);
	ray_dir_y =  sin(ray_angle);
	i = 0;
	(void)data_pixel;
	while (1)
	{
		map_x = (int)(ray_x / 32);
		map_y = (int)(ray_y / 32);
		if (data->map_data.map[map_y][map_x] == '1')
			break ;
		my_mlx_pixel_put(data_pixel,(int)ray_x,(int)ray_y,0xFF0000);
		//mlx_pixel_put(data_mlx->mlx_ptr, data_mlx->window_ptr, (int)ray_x,
		//(int)ray_y, 0xFF0000);
		//printf("ray_x = %f ray_y = %f\n",ray_x - ray_dir_x,ray_y - ray_dir_y);
		ray_x += ray_dir_x * 1;
		ray_y += ray_dir_y * 1;
	}
}

int	put_segment(t_window *data_mlx, t_data_game *data_game,t_data_pixel *data_pixel)
{
	int i;
	int j;
	int x;
	int y;

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

	
	while (data_game->map_data.map[i])
	{
		j = 0;
		while (data_game->map_data.map[i][j])
		{
			y = 0;
			if (data_game->map_data.map[i][j] == '1')
			{
				while (y < 32)
				{
					x = 0;
					while (x < 32)
					{
						
						my_mlx_pixel_put(data_pixel,j * 32 + x,i *32 + y,0xFFFFFF);
						// mlx_pixel_put(data_mlx->mlx_ptr, data_mlx->window_ptr, j
						// 	* 32 + x, i * 32 + y, 0xFFFFFF);
						x++;
					}
					y++;
				}
			}
			if (data_game->map_data.map[i][j] == '0')
			{
				y = 0;
				while (y < 32)
				{
					x = 0;
					while (x < 32)
					{
						my_mlx_pixel_put(data_pixel,j * 32 + x,i *32 + y,0xF00FFF);
						x++;
					}
					y++;
				}
			}
			if (data_game->map_data.map[i][j] == 'N')
			{
				
				if(data_game->flag.fisrt_pos_flag == 0)
				{
					data_game->player_pos.player_pos_x = j;
					data_game->player_pos.player_pos_y = i;
					data_game->player_pos.player_angle = -M_PI / 2;
					data_game->flag.fisrt_pos_flag = 1;
				}
			}
			j++;
		}
		i++;
	}
	
	y = 0;
    while (y < 32)
    {
        x = 0;
        while (x < 32)
        {
			my_mlx_pixel_put(data_pixel,(int)(data_game->player_pos.player_pos_x * 32) + x,(int)(data_game->player_pos.player_pos_y * 32) + y, 0x000066);
            x++;
        }
        y++;
    }
	float fov = M_PI / 3;
	int num_rays = 1920;
	float ray_angle;
	i = 0;
	
	while (i < num_rays)
	{
		ray_angle = data_game->player_pos.player_angle - fov/2 + (fov * i / num_rays);
		ray_cast(data_game, data_mlx, ray_angle,data_pixel);
		i++;
	}
	mlx_put_image_to_window(data_mlx->mlx_ptr,data_mlx->window_ptr,data_pixel->img_ptr,0,0);
	return (0);
}
