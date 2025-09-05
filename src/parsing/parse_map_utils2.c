/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:27:31 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/05 10:33:39 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clean_map(t_data_game *data_game)
{
	int	i;

	i = data_game->map_data.height - 1;
	while (data_game->map_data.map[i][0] == '\n')
	{
		free(data_game->map_data.map[i]);
		i--;
	}
	data_game->map_data.map[i + 1] = NULL;
}

int	check_map(t_data_game *data_game)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	clean_map(data_game);
	map = data_game->map_data.map;
	while (map[i])
	{
		j = 0;
		if (map[i][0] == '\n')
			return (-1);
		while (map[i][j])
		{
			if (check_char(map[i][j], data_game) == -1 || check_zero(i, j,
					map) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (data_game->flag.player_flag == 0)
		return (-1);
	return (0);
}

int	malloc_map(t_data_game *data_game)
{
	int	j;

	if (data_game->map_data.height <= 2)
		return (-1);
	data_game->map_data.map = malloc(sizeof(char *)
			* (data_game->map_data.height + 1));
	if (!data_game->map_data.map)
		return (-1);
	j = 0;
	while (j < data_game->map_data.height)
	{
		data_game->map_data.map[j] = malloc(1);
		if (!data_game->map_data.map[j])
			return (free_split(data_game->map_data.map), -1);
		data_game->map_data.map[j][0] = 0;
		j++;
	}
	return (0);
}
