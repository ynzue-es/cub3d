/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:22:58 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/09 10:49:37 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
}

int	convert_hex(char **str, int flag_ceil_floor, t_data_game *data_game)
{
	if (flag_ceil_floor == 0)
	{
		str[0] = switch_hex(data_game->ceil_floor.ceil[0]);
		if (!str[0])
			return (-1);
		str[1] = switch_hex(data_game->ceil_floor.ceil[1]);
		if (!str[1])
			return (-1);
		str[2] = switch_hex(data_game->ceil_floor.ceil[2]);
		if (!str[2])
			return (-1);
	}
	else
	{
		str[0] = switch_hex(data_game->ceil_floor.floor[0]);
		if (!str[0])
			return (-1);
		str[1] = switch_hex(data_game->ceil_floor.floor[1]);
		if (!str[1])
			return (-1);
		str[2] = switch_hex(data_game->ceil_floor.floor[2]);
		if (!str[2])
			return (-1);
	}
	return (0);
}
