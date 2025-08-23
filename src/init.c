/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:50 by yannis            #+#    #+#             */
/*   Updated: 2025/08/23 15:22:53 by yannis           ###   ########.fr       */
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
