/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:09:04 by yannis            #+#    #+#             */
/*   Updated: 2025/09/03 13:07:50 by yannis           ###   ########.fr       */
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
int	hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	hex_to_int(char *hex_str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (hex_str[i])
	{
		result = result * 16 + hex_char_to_int(hex_str[i]);
		i++;
	}
	return (result);
}

char	*switch_hex(int n)
{
	char	*hex;
	char	*base;
	int		i;

	base = "0123456789abcdef";
	hex = malloc(100);
	i = 0;
	while (n > 0)
	{
		hex[i] = (base[n % 16]);
		n = n / 16;
		i++;
	}
	hex[i] = '\0';
	return (hex);
}
int	switch_tab_int(t_data_game *data_game, int flag_ceil_floor)
{
	char	*str;
	char	*str1;
	char	*str2;
	char	*new;
	int		result;

	if (flag_ceil_floor == 0)
	{
		str = switch_hex(data_game->ceil_floor.ceil[0]);
		str1 = switch_hex(data_game->ceil_floor.ceil[1]);
		str2 = switch_hex(data_game->ceil_floor.ceil[2]);
	}
	else
	{
		str = switch_hex(data_game->ceil_floor.floor[0]);
		str1 = switch_hex(data_game->ceil_floor.floor[1]);
		str2 = switch_hex(data_game->ceil_floor.floor[2]);
	}
	new = ft_strcat(str, str1);
	new = ft_strcat(new, str2);
	result = hex_to_int(new);
	return (result);
}
void	draw_background(t_data_game *data_game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < data_game->data_mlx.height)
	{
		if (y < (data_game->data_mlx.height / 2))
			color = switch_tab_int(data_game, 0);
		else
			color = switch_tab_int(data_game, 1);
		x = 0;
		while (x < data_game->data_mlx.width)
		{
			my_mlx_pixel_put(&data_game->data_pixel, x, y, color);
			x++;
		}
		y++;
	}
}

static inline unsigned int	get_texel(t_wall_texture *tex, int x, int y)
{
	char	*p;

	p = tex->addr + y * tex->line_length + x * (tex->bits_per_pixel / 8);
	return (*(unsigned int *)p);
}

enum
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST
};

static inline int	pick_tex_id(int hit_side, int step_x, int step_y)
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

int	put_wall_segment(t_data_game *g, int x, float perpWallDist, int hit_side,
		float ray_angle)
{
	float			proj_plane;
	float			angle_diff;
	float			corrected_dist;
	int				wall_height;
	int				draw_start;
	int				draw_end;
	float			wallX;
	int				tex_id;
	t_wall_texture	*tex;
	int				texX;
	float			step;
	float			texPos;
	int				texY;
	unsigned int	color;

	// Plan de projection et correction fish-eye
	proj_plane = (g->data_mlx.width * 0.5f) / tanf(g->fov * 0.5f);
	angle_diff = ray_angle - g->player_pos.player_angle;
	corrected_dist = perpWallDist * cosf(angle_diff);
	// Hauteur et bornes de dessin
	wall_height = (int)(proj_plane / fmaxf(corrected_dist, 0.0001f));
	draw_start = (g->data_mlx.height - wall_height) / 2;
	draw_end = draw_start + wall_height - 1;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= g->data_mlx.height)
		draw_end = g->data_mlx.height - 1;
	// Coordonnée d'impact fractionnelle le long de la paroi
	wallX = (hit_side == 0) ? g->player_pos.player_pos_y + perpWallDist
		* g->ray_data.ray_dir_y : g->player_pos.player_pos_x + perpWallDist
		* g->ray_data.ray_dir_x;
	wallX -= floorf(wallX);
	// Choix de la texture selon la face frappée
	tex_id = pick_tex_id(hit_side, g->ray_data.stepX, g->ray_data.stepY);
	tex = &g->wall_texture[tex_id];
	// Colonne de tex (miroir selon la face pour garder l'orientation)
	texX = (int)(wallX * (float)tex->width);
	if ((hit_side == 0 && g->ray_data.ray_dir_x > 0) ||
		// paroi verticale vue depuis l'ouest
		(hit_side == 1 && g->ray_data.ray_dir_y < 0))  
			// paroi horizontale vue depuis le sud
		texX = tex->width - texX - 1;
	// Pas vertical dans la texture
	step = (float)tex->height / (float)wall_height;
	texPos = (draw_start - (g->data_mlx.height / 2 - wall_height / 2)) * step;
	for (int y = draw_start; y <= draw_end; ++y)
	{
		texY = (int)texPos;
		if (texY < 0)
			texY = 0;
		if (texY >= tex->height)
			texY = tex->height - 1;
		color = get_texel(tex, texX, texY);
		my_mlx_pixel_put(&g->data_pixel, x, y, color);
		texPos += step;
	}
	return (0);
}
