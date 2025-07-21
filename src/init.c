/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:19:50 by yannis            #+#    #+#             */
/*   Updated: 2025/07/21 15:25:53 by yannis           ###   ########.fr       */
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
	return (0);
}
