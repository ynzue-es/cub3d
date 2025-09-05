/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:50 by yannis            #+#    #+#             */
/*   Updated: 2025/09/05 09:40:06 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_data_game(t_data_game *data_game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data_game->all_wall[i].direction = NULL;
		data_game->all_wall[i++].texure_file = NULL;
	}
	data_game->count_walls = 0;
	i = 0;
	while (i < 3)
	{
		data_game->ceil_floor.ceil[i] = 0;
		data_game->ceil_floor.floor[i++] = 0;
	}
	data_game->map_data.height = 0;
	data_game->map_data.width = 0;
	data_game->data_mlx.height = 1090;
	data_game->data_mlx.width = 2000;
	data_game->tile_size = 16;
	return (0);
}

int	init_flag(t_flag *flag)
{
	flag->ceil_flag = 0;
	flag->floor_flag = 0;
	flag->east_flag = 0;
	flag->south_flag = 0;
	flag->north_flag = 0;
	flag->west_flag = 0;
	flag->player_flag = 0;
	flag->fisrt_pos_flag = 0;
	return (0);
}

int	init_mlx(t_data_game **g)
{
	(*g)->data_mlx.mlx_ptr = mlx_init();
	if (!(*g)->data_mlx.mlx_ptr)
		return (1);
	(*g)->data_mlx.window_ptr = mlx_new_window((*g)->data_mlx.mlx_ptr,
			(*g)->data_mlx.width, (*g)->data_mlx.height, "cub3d");
	if (!(*g)->data_mlx.window_ptr)
		return (1);
	(*g)->data_pixel.img_ptr = mlx_new_image((*g)->data_mlx.mlx_ptr,
			(*g)->data_mlx.width, (*g)->data_mlx.height);
	if (!(*g)->data_pixel.img_ptr)
		return (1);
	(*g)->data_pixel.addr = mlx_get_data_addr((*g)->data_pixel.img_ptr,
			&(*g)->data_pixel.bits_per_pixel, &(*g)->data_pixel.line_length,
			&(*g)->data_pixel.endian);
	if (!(*g)->data_pixel.addr)
		return (1);
	return (0);
}

int	init_mlx_texture(t_data_game **g, int i)
{
	(*g)->wall_t[i].img_ptr = mlx_xpm_file_to_image((*g)->data_mlx.mlx_ptr,
			(*g)->all_wall[i].texure_file, &(*g)->wall_t[i].width,
			&(*g)->wall_t[i].height);
	if (!(*g)->wall_t[i].img_ptr)
		return (1);
	(*g)->wall_t[i].addr = mlx_get_data_addr((*g)->wall_t[i].img_ptr,
			&(*g)->wall_t[i].bits_per_pixel, &(*g)->wall_t[i].line_length,
			&(*g)->wall_t[i].endian);
	if (!(*g)->wall_t[i].addr)
		return (1);
	return (0);
}
