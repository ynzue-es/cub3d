/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:10:06 by yannis            #+#    #+#             */
/*   Updated: 2025/09/05 10:32:52 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

unsigned int	get_texel(t_wall_texture *tex, int x, int y)
{
	char	*p;

	p = tex->addr + y * tex->line_length + x * (tex->bits_per_pixel / 8);
	return (*(unsigned int *)p);
}

int	pick_tex_id(int hit_side, int step_x, int step_y)
{
	if (hit_side == 0)
	{
		if (step_x > 0)
			return (TEX_EAST);
		else
			return (TEX_WEST);
	}
	else
	{
		if (step_y > 0)
			return (TEX_SOUTH);
		else
			return (TEX_NORTH);
	}
}

float	projection_plane(t_data_game *g)
{
	return ((g->data_mlx.width * 0.5f) / tanf(g->fov * 0.5f));
}

float	hit_point_fraction(t_data_game *g, int hit_side, float perpWallDist)
{
	float	wall_x;

	if (hit_side == 0)
		wall_x = g->player_pos.player_pos_y + perpWallDist
			* g->ray_data.ray_dir_y;
	else
		wall_x = g->player_pos.player_pos_x + perpWallDist
			* g->ray_data.ray_dir_x;
	wall_x -= floorf(wall_x);
	return (wall_x);
}

void	draw_textured_column(t_data_game *g, int x, t_wall_draw *wd,
		t_tex_coords *tc)
{
	float			tex_pos;
	int				tex_y;
	unsigned int	color;
	int				y;

	y = wd->draw_start;
	tex_pos = tc->tex_pos_0;
	while (y <= wd->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tc->tex->height)
			tex_y = tc->tex->height - 1;
		color = get_texel(tc->tex, tc->tex_x, tex_y);
		my_mlx_pixel_put(&g->data_pixel, x, y, color);
		tex_pos += tc->step;
		y++;
	}
}
