/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:09:04 by yannis            #+#    #+#             */
/*   Updated: 2025/08/26 10:08:51 by engiusep         ###   ########.fr       */
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
int hex_char_to_int(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
    if (c >= 'A' && c <= 'F')
        return (c - 'A' + 10);
    return (0);
}

int hex_to_int(char *hex_str)
{
    int result = 0;
    int i = 0;
    
    while (hex_str[i])
    {
        result = result * 16 + hex_char_to_int(hex_str[i]);
        i++;
    }
    return (result);
}

char *switch_hex(int n)
{
    char *hex;
    char *base = "0123456789abcdef";
    hex = malloc(100);
    int i;
  
    i = 0;
    while(n > 0)
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
    int result;

    
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
    //printf("%d\n",result);
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
			color = switch_tab_int(data_game,0);
		else
			color = switch_tab_int(data_game,1);
		x = 0;
		while (x < data_game->data_mlx.width)
		{
			my_mlx_pixel_put(&data_game->data_pixel, x, y, color);
			x++;
		}
		y++;
	}
}

// int put_wall_segement(t_data_game *g, int x, float perpWallDist, int hit_side, float ray_angle)
// {
//     float fov = g->fov; 
//     float proj_plane = (g->data_mlx.width * 0.5f) / tanf(fov * 0.5f);
    
//     float angle_diff = ray_angle - g->player_pos.player_angle;
//     float corrected_dist = perpWallDist * cosf(angle_diff);
    
//     int wall_height = (int)(proj_plane / corrected_dist);
//     int draw_start = (g->data_mlx.height - wall_height) / 2;
//     int draw_end   = draw_start + wall_height;
//     if (draw_start < 0) draw_start = 0;
//     if (draw_end > g->data_mlx.height) draw_end = g->data_mlx.height;
//     int shade = (hit_side == 0) ? 0xAA : 0xFF;
//     int color = (shade << 16);
//     int y = draw_start;

//     while (y < draw_end)
//     {
//         my_mlx_pixel_put(&g->data_pixel, x, y, color);
//         y++;
//     }
//     return 0;
// }

static inline unsigned int get_texel(t_wall_texture *tex, int x, int y)
{
    char *p = tex->addr + y * tex->line_length + x * (tex->bits_per_pixel / 8);
    return *(unsigned int *)p; // MLX (42) stocke en BGRA/ARGB selon OS, ça fonctionne pour peindre
}

int put_wall_segement(t_data_game *g, int x, float perpWallDist, int hit_side, float ray_angle)
{
    // Plan de projection basé sur FOV horizontal
    float proj_plane = (g->data_mlx.width * 0.5f) / tanf(g->fov * 0.5f);

    float angle_diff = ray_angle - g->player_pos.player_angle;
    float corrected_dist = perpWallDist * cosf(angle_diff);

    // Hauteur de la bande projetée
    int wall_height = (int)(proj_plane / corrected_dist);
    int draw_start = (g->data_mlx.height - wall_height) / 2;
    int draw_end   = draw_start + wall_height - 1;
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= g->data_mlx.height) draw_end = g->data_mlx.height - 1;

    // --- position du hit sur le mur (fraction 0..1)
    float wallX;
    if (hit_side == 0)
        wallX = g->player_pos.player_pos_y + perpWallDist * g->ray_data.ray_dir_y;
    else
        wallX = g->player_pos.player_pos_x + perpWallDist * g->ray_data.ray_dir_x;
    wallX -= floorf(wallX);

    // colonne de texture
    int texX = (int)(wallX * (float)g->wall_texture.width);
    if ((hit_side == 0 && g->ray_data.ray_dir_x > 0) ||
        (hit_side == 1 && g->ray_data.ray_dir_y < 0))
        texX = g->wall_texture.width - texX - 1;

    // pas vertical dans la texture
    float step = (float)g->wall_texture.height / (float)wall_height;
    float texPos = (draw_start - (g->data_mlx.height / 2 - wall_height / 2)) * step;

    for (int y = draw_start; y <= draw_end; ++y)
    {
        int texY = (int)texPos;
        if (texY < 0) texY = 0;
        if (texY >= g->wall_texture.height) texY = g->wall_texture.height - 1;

        unsigned int color = get_texel(&g->wall_texture, texX, texY);
        my_mlx_pixel_put(&g->data_pixel, x, y, color);

        texPos += step;
    }
    return 0;
}
