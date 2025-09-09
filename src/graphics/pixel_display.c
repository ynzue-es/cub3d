/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:09:04 by yannis            #+#    #+#             */
/*   Updated: 2025/09/09 10:34:45 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	my_mlx_pixel_put(t_data_pixel *data_pixel, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 2000 || y >= 1090)
		return ;
	dst = data_pixel->addr + (y * data_pixel->line_length + x
			* (data_pixel->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_background(t_data_game *data_game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < data_game->data_mlx.height)
	{
		color = switch_tab_int(data_game, y > (data_game->data_mlx.height / 2));
		if (color == -1)
			return (-1);
		x = 0;
		while (x < data_game->data_mlx.width)
		{
			my_mlx_pixel_put(&data_game->data_pixel, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

/* Calcule les coordonnées de texture pour la colonne :
détermine la face du mur (texture) touchée
calcule la position X dans la texture (t.tex_x) selon le point d’impact
prépare le pas vertical (t.step) et la position initiale (t.tex_pos_0)
*/
t_tex_coords	compute_texture_coords(t_data_game *g, int hit_side,
		float perp_wall_dist, t_wall_draw *wd)
{
	t_tex_coords	t;
	float			wall_x;

	wall_x = hit_point_fraction(g, hit_side, perp_wall_dist);
	t.tex_id = pick_tex_id(hit_side, g->ray_data.step_x, g->ray_data.step_y);
	t.tex = &g->wall_t[t.tex_id];
	t.tex_x = (int)(wall_x * (float)t.tex->width);
	if ((hit_side == 0 && g->ray_data.ray_dir_x > 0) || (hit_side == 1
			&& g->ray_data.ray_dir_y < 0))
		t.tex_x = t.tex->width - t.tex_x - 1;
	t.step = (float)t.tex->height / (float)wd->wall_height;
	t.tex_pos_0 = (wd->draw_start - (g->data_mlx.height / 2 - wd->wall_height
				/ 2)) * t.step;
	return (t);
}

/* Calcule la géométrie d’affichage de la colonne murale :
hauteur projetée en pixels, position de départ/fin à l’écran
intervale des bornes dans la fenêtre d’affichage
*/
t_wall_draw	compute_wall_draw(t_data_game *g, float corrected_dist)
{
	t_wall_draw	d;
	float		proj_plane;

	proj_plane = projection_plane(g);
	d.wall_height = (int)(proj_plane / fmaxf(corrected_dist, 0.0001f));
	d.draw_start = (g->data_mlx.height - d.wall_height) / 2;
	d.draw_end = d.draw_start + d.wall_height - 1;
	if (d.draw_start < 0)
		d.draw_start = 0;
	if (d.draw_end >= g->data_mlx.height)
		d.draw_end = g->data_mlx.height - 1;
	return (d);
}

/* Dessine une colonne de mur à l’écran en appliquant :
la correction anti “fish-eye” (cos(angle_diff))
le calcul des bornes de la colonne (compute_wall_draw)
les coordonnées de texture (compute_texture_coords)
puis le rendu texturé de la colonne (draw_textured_column)
 */
int	put_wall_segment(t_data_game *g, int x, float perp_wall_dist, int hit_side)
{
	float			angle_diff;
	float			corr;
	t_wall_draw		wd;
	t_tex_coords	tc;

	angle_diff = g->ray_data.ray_angle - g->player_pos.player_angle;
	corr = perp_wall_dist * cosf(angle_diff);
	wd = compute_wall_draw(g, corr);
	tc = compute_texture_coords(g, hit_side, perp_wall_dist, &wd);
	draw_textured_column(g, x, &wd, &tc);
	return (0);
}
