/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/23 15:22:31 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	put_wall(t_data_game *data_game, int ray_x, int ray_y)
{
	void	*wall;
	int		h;
	int		w;

	wall = mlx_xpm_file_to_image(data_game->data_mlx.mlx_ptr, "wall.xpm", &w,
			&h);
	mlx_put_image_to_window(data_game->data_mlx.mlx_ptr,
		data_game->data_mlx.window_ptr, wall, ray_x, ray_y);
	return (0);
}

void	ray_cast(t_data_game *data_game, float ray_angle, int i)
{
	data_game->ray_data.ray_x = data_game->player_pos.player_pos_x
		* data_game->tile_size;
	data_game->ray_data.ray_y = data_game->player_pos.player_pos_y
		* data_game->tile_size;
	data_game->ray_data.ray_dir_x = cos(ray_angle);
	data_game->ray_data.ray_dir_y = sin(ray_angle);
	while (1)
	{
		data_game->ray_data.map_x = (int)(data_game->ray_data.ray_x
				/ data_game->tile_size);
		data_game->ray_data.map_y = (int)(data_game->ray_data.ray_y
				/ data_game->tile_size);
		if (data_game->map_data.map[data_game->ray_data.map_y][data_game->ray_data.map_x] == '1')
			break ;
		data_game->ray_data.ray_x += data_game->ray_data.ray_dir_x * 1;
		data_game->ray_data.ray_y += data_game->ray_data.ray_dir_y * 1;
	}
	put_wall_segement(data_game, i, ray_angle);
}

int	find_player_start(t_data_game *data_game)
{
	int	x;
	int	y;

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

int	game_view(t_data_game *data_game)
{
	int		i;
	float	fov;
	int		num_rays;
	float	ray_angle;

	fov = M_PI / 3;
	num_rays = data_game->data_mlx.width;
	i = 0;
	find_player_start(data_game);
	draw_background(data_game);
	while (i < num_rays)
	{
		ray_angle = data_game->player_pos.player_angle - fov / 2 + (fov * i
				/ num_rays);
		ray_cast(data_game, ray_angle, i);
		i++;
	}
	mlx_put_image_to_window(data_game->data_mlx.mlx_ptr,
		data_game->data_mlx.window_ptr, data_game->data_pixel.img_ptr, 0, 0);
	return (0);
}
