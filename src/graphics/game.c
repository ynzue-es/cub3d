/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/24 12:04:13 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void nearest_side(t_data_game *g)
{
    if (g->ray_data.sideDistX < g->ray_data.sideDistY) {
        g->ray_data.sideDistX += g->ray_data.deltaDistX;
        g->ray_data.map_x += g->ray_data.stepX;
        g->ray_data.hit_side = 0;
    } else {
        g->ray_data.sideDistY += g->ray_data.deltaDistY;
        g->ray_data.map_y += g->ray_data.stepY;
        g->ray_data.hit_side = 1;
    }
}

void	ray_cast(t_data_game *g, float ray_angle, int i)
{
	g->ray_data.map_x = (int)g->player_pos.player_pos_x;
	g->ray_data.map_y = (int)g->player_pos.player_pos_y;

	// direction du rayon
	g->ray_data.ray_dir_x = cos(ray_angle);
	g->ray_data.ray_dir_y = sin(ray_angle);
	//dist joueur vers bord premiere case
	g->ray_data.deltaDistX = fabs(1 / g->ray_data.ray_dir_x);
	g->ray_data.deltaDistY = fabs(1 / g->ray_data.ray_dir_y);
	//direction des step X
	if (g->ray_data.ray_dir_x < 0)
	{
		g->ray_data.stepX = -1;
		g->ray_data.sideDistX = (g->player_pos.player_pos_x - g->ray_data.map_x) * g->ray_data.deltaDistX;
	}
	else
	{
		g->ray_data.stepX = 1;
		g->ray_data.sideDistX = (g->ray_data.map_x + 1 - g->player_pos.player_pos_x) * g->ray_data.deltaDistX;
	}
	//direction des step Y
	if (g->ray_data.ray_dir_y < 0)
	{
		g->ray_data.stepY = -1;
		g->ray_data.sideDistY = (g->player_pos.player_pos_y - g->ray_data.map_y) * g->ray_data.deltaDistY;
	}
	else
	{
		g->ray_data.stepY = 1;
		g->ray_data.sideDistY = (g->ray_data.map_y + 1 - g->player_pos.player_pos_y) * g->ray_data.deltaDistY;
	}
	
	while (1)
	{
		// ici pour chaque tile on va regarder le side le plus proche
		nearest_side(g);
		if (g->map_data.map[g->ray_data.map_y][g->ray_data.map_x] == '1')
			break;
	}
	
	// fish eye
	float perpWallDist = (g->ray_data.hit_side == 0)
	? (g->ray_data.map_x - g->player_pos.player_pos_x + (1 - g->ray_data.stepX) * 0.5f) / g->ray_data.ray_dir_x
	: (g->ray_data.map_y - g->player_pos.player_pos_y + (1 - g->ray_data.stepY) * 0.5f) / g->ray_data.ray_dir_y;
	
	put_wall_segement(g, i, perpWallDist, g->ray_data.hit_side);
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
			// changer N unique
			if (g->map_data.map[x][y] == 'N')
			{
				g->player_pos.player_pos_x = x;
				g->player_pos.player_pos_y = y;
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
	mlx_put_image_to_window(g->data_mlx.mlx_ptr,
		g->data_mlx.window_ptr, g->data_pixel.img_ptr, 0, 0);
	return (0);
}
