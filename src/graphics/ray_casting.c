/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:12:17 by yannis            #+#    #+#             */
/*   Updated: 2025/09/03 10:28:24 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	nearest_side(t_data_game *g)
{
	if (g->ray_data.sideDistX < g->ray_data.sideDistY)
	{
		g->ray_data.sideDistX += g->ray_data.deltaDistX;
		g->ray_data.map_x += g->ray_data.stepX;
		g->ray_data.hit_side = 0;
	}
	else
	{
		g->ray_data.sideDistY += g->ray_data.deltaDistY;
		g->ray_data.map_y += g->ray_data.stepY;
		g->ray_data.hit_side = 1;
	}
}

void	step_ray_x(t_data_game *g)
{
	if (g->ray_data.ray_dir_x < 0)
	{
		g->ray_data.stepX = -1;
		g->ray_data.sideDistX = (g->player_pos.player_pos_x - g->ray_data.map_x)
			* g->ray_data.deltaDistX;
	}
	else
	{
		g->ray_data.stepX = 1;
		g->ray_data.sideDistX = (g->ray_data.map_x + 1
				- g->player_pos.player_pos_x) * g->ray_data.deltaDistX;
	}
}

void	step_ray_y(t_data_game *g)
{
	if (g->ray_data.ray_dir_y < 0)
	{
		g->ray_data.stepY = -1;
		g->ray_data.sideDistY = (g->player_pos.player_pos_y - g->ray_data.map_y)
			* g->ray_data.deltaDistY;
	}
	else
	{
		g->ray_data.stepY = 1;
		g->ray_data.sideDistY = (g->ray_data.map_y + 1
				- g->player_pos.player_pos_y) * g->ray_data.deltaDistY;
	}
}

void	ray_cast(t_data_game *g, float ray_angle, int i)
{
	float	perpWallDist;

	g->ray_data.map_x = (int)g->player_pos.player_pos_x;
	g->ray_data.map_y = (int)g->player_pos.player_pos_y;
	g->ray_data.ray_dir_x = cos(ray_angle);
	g->ray_data.ray_dir_y = sin(ray_angle);
	g->ray_data.deltaDistX = fabs(1 / g->ray_data.ray_dir_x);
	g->ray_data.deltaDistY = fabs(1 / g->ray_data.ray_dir_y);
	step_ray_x(g);
	step_ray_y(g);
	while (1)
	{
		nearest_side(g);
		if (g->map_data.map[g->ray_data.map_y][g->ray_data.map_x] == '1')
			break ;
	}
	if (g->ray_data.hit_side == 0)
		perpWallDist = (g->ray_data.map_x - g->player_pos.player_pos_x + (1
					- g->ray_data.stepX) * 0.5f) / g->ray_data.ray_dir_x;
	else
		perpWallDist = (g->ray_data.map_y - g->player_pos.player_pos_y + (1
					- g->ray_data.stepY) * 0.5f) / g->ray_data.ray_dir_y;
	put_wall_segment(g, i, perpWallDist, g->ray_data.hit_side, ray_angle);
}
