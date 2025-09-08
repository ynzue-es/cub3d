/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:22:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/08 14:32:12 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	convet_hex(char **str, int flag_ceil_floor, t_data_game *data_game)
{
	if (flag_ceil_floor == 0)
	{
		str[0] = switch_hex(data_game->ceil_floor.ceil[0]);
		str[1] = switch_hex(data_game->ceil_floor.ceil[1]);
		str[2] = switch_hex(data_game->ceil_floor.ceil[2]);
	}
	else
	{
		str[0] = switch_hex(data_game->ceil_floor.floor[0]);
		str[1] = switch_hex(data_game->ceil_floor.floor[1]);
		str[2] = switch_hex(data_game->ceil_floor.floor[2]);
	}
}
