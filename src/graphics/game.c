/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/23 14:19:30 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	put_wall(t_data_game *data ,int ray_x,int ray_y)
{
	void *wall;
	int h;
	int w;

	wall = mlx_xpm_file_to_image(data->data_mlx->mlx_ptr,"wall.xpm", &w, &h);
	mlx_put_image_to_window(data->data_mlx->mlx_ptr,data->data_mlx->window_ptr,wall,ray_x,ray_y);
	return (0);
}

void	ray_cast(t_data_game *data, float ray_angle, int i)
{
	data->ray_data.ray_x = data->player_pos.player_pos_x * 16 + 8;
	data->ray_data.ray_y = data->player_pos.player_pos_y * 16 + 8;
	
	data->ray_data.ray_dir_x =  cos(ray_angle);
	data->ray_data.ray_dir_y =  sin(ray_angle);
	while (1)
	{
		data->ray_data.map_x = (int)(data->ray_data.ray_x / 16);
		data->ray_data.map_y = (int)(data->ray_data.ray_y / 16);
		
		if (data->map_data.map[data->ray_data.map_y][data->ray_data.map_x] == '1')
			break ;
		data->ray_data.ray_x += data->ray_data.ray_dir_x * 1;
		data->ray_data.ray_y += data->ray_data.ray_dir_y * 1;
	}
	put_wall_segement(data, i, ray_angle);
}

int find_player_start(t_data_game *data_game)
{
	int x;
	int y;
	
	x = 0;
	while (data_game->map_data.map[x])
	{
		y = 0;
		while (data_game->map_data.map[x][y])
		{
			// changer N unique
			if (data_game->map_data.map[x][y] == 'N')
			{
				data_game->player_pos.player_pos_x = x;
				data_game->player_pos.player_pos_y = y;
				data_game->player_pos.player_angle = -M_PI / 2;
				data_game->map_data.map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	game_view(t_window *data_mlx, t_data_game *data_game,t_data_pixel *data_pixel)
{
	int i;
	float fov = M_PI / 3;
	int num_rays = 2000;
	float ray_angle;

	find_player_start(data_game);

	i = 0;
	draw_background(data_pixel);
	while (i < num_rays)
	{
		ray_angle = data_game->player_pos.player_angle - fov/2 + (fov * i / num_rays);
		ray_cast(data_game, ray_angle, i);
		i++;
	}
	mlx_put_image_to_window(data_mlx->mlx_ptr,data_mlx->window_ptr,data_pixel->img_ptr,0,0);
	return (0);
}
