/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/09 10:32:02 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	start_pos(float player_angle, t_data_game *g, int x, int y)
{
	g->player_pos.player_pos_x = y;
	g->player_pos.player_pos_y = x;
	g->player_pos.player_angle = player_angle;
	g->map_data.map[x][y] = '0';
}

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
			if (g->map_data.map[x][y] == 'N')
				start_pos(-M_PI / 2, g, x, y);
			if (g->map_data.map[x][y] == 'S')
				start_pos(M_PI / 2, g, x, y);
			if (g->map_data.map[x][y] == 'W')
				start_pos(0, g, x, y);
			if (g->map_data.map[x][y] == 'E')
				start_pos(M_PI, g, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

int	game_view(t_data_game *g)
{
	int	i;
	int	num_rays;

	g->fov = M_PI / 3;
	num_rays = g->data_mlx.width;
	i = 0;
	find_player_start(g);
	if (draw_background(g) == -1)
		return (-1);
	while (i < num_rays)
	{
		g->ray_data.ray_angle = g->player_pos.player_angle - g->fov / 2
			+ (g->fov * i / num_rays);
		ray_cast(g, i);
		i++;
	}
	mlx_put_image_to_window(g->data_mlx.mlx_ptr, g->data_mlx.window_ptr,
		g->data_pixel.img_ptr, 0, 0);
	return (0);
}
