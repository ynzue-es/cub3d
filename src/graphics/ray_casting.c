/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:12:17 by yannis            #+#    #+#             */
/*   Updated: 2025/09/09 09:58:36 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// Choisit si le rayon avance d’abord sur l’axe x ou y méthode DDA
void	nearest_side(t_data_game *g)
{
	if (g->ray_data.side_dist_x < g->ray_data.side_dist_y)
	{
		g->ray_data.side_dist_x += g->ray_data.delta_dist_x;
		g->ray_data.map_x += g->ray_data.step_x;
		g->ray_data.hit_side = 0;
	}
	else
	{
		g->ray_data.side_dist_y += g->ray_data.delta_dist_y;
		g->ray_data.map_y += g->ray_data.step_y;
		g->ray_data.hit_side = 1;
	}
}

// Initialise la direction et la distance du rayon sur l’axe x
void	step_ray_x(t_data_game *g)
{
	if (g->ray_data.ray_dir_x < 0)
	{
		g->ray_data.step_x = -1;
		g->ray_data.side_dist_x = (g->player_pos.player_pos_x
				- g->ray_data.map_x) * g->ray_data.delta_dist_x;
	}
	else
	{
		g->ray_data.step_x = 1;
		g->ray_data.side_dist_x = (g->ray_data.map_x + 1
				- g->player_pos.player_pos_x) * g->ray_data.delta_dist_x;
	}
}

// Initialise la direction et la distance du rayon sur l’axe y
void	step_ray_y(t_data_game *g)
{
	if (g->ray_data.ray_dir_y < 0)
	{
		g->ray_data.step_y = -1;
		g->ray_data.side_dist_y = (g->player_pos.player_pos_y
				- g->ray_data.map_y) * g->ray_data.delta_dist_y;
	}
	else
	{
		g->ray_data.step_y = 1;
		g->ray_data.side_dist_y = (g->ray_data.map_y + 1
				- g->player_pos.player_pos_y) * g->ray_data.delta_dist_y;
	}
}

/* Lance un rayon, trouve le premier mur touché avec DDA, 
	puis calcule la distance pour dessiner la colonne correspondante
*/
void	ray_cast(t_data_game *g, int i)
{
	float	perp_wall_dist;

	g->ray_data.map_x = (int)g->player_pos.player_pos_x;
	g->ray_data.map_y = (int)g->player_pos.player_pos_y;
	g->ray_data.ray_dir_x = cos(g->ray_data.ray_angle);
	g->ray_data.ray_dir_y = sin(g->ray_data.ray_angle);
	g->ray_data.delta_dist_x = fabs(1 / g->ray_data.ray_dir_x);
	g->ray_data.delta_dist_y = fabs(1 / g->ray_data.ray_dir_y);
	step_ray_x(g);
	step_ray_y(g);
	while (1)
	{
		nearest_side(g);
		if (g->map_data.map[g->ray_data.map_y][g->ray_data.map_x] == '1')
			break ;
	}
	if (g->ray_data.hit_side == 0)
		perp_wall_dist = (g->ray_data.map_x - g->player_pos.player_pos_x + (1
					- g->ray_data.step_x) * 0.5f) / g->ray_data.ray_dir_x;
	else
		perp_wall_dist = (g->ray_data.map_y - g->player_pos.player_pos_y + (1
					- g->ray_data.step_y) * 0.5f) / g->ray_data.ray_dir_y;
	put_wall_segment(g, i, perp_wall_dist, g->ray_data.hit_side);
}
