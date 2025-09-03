/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/03 13:07:35 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	find_player_start(t_data_game *g)
{
	int	x;
	int	y;

	x = 0;
	while (g->map_data.map[x])
	{
		y = 0;
		while (g->map_data.map[x][y])
		{
			// changer N unique
			if (g->map_data.map[x][y] == 'N')
			{
				g->player_pos.player_pos_x = y;
				g->player_pos.player_pos_y = x;
				g->player_pos.player_angle = -M_PI / 2;
				g->map_data.map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	game_view(t_data_game *g)
{
	int		i;
	int		num_rays;
	float	ray_angle;

	g->fov = M_PI / 3;
	num_rays = g->data_mlx.width;
	i = 0;
	find_player_start(g);
	draw_background(g);
	while (i < num_rays)
	{
		ray_angle = g->player_pos.player_angle - g->fov / 2 + (g->fov * i
				/ num_rays);
		ray_cast(g, ray_angle, i);
		i++;
	}
	mlx_put_image_to_window(g->data_mlx.mlx_ptr, g->data_mlx.window_ptr,
		g->data_pixel.img_ptr, 0, 0);
	return (0);
}
