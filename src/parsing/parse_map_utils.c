/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:26:05 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/05 10:33:59 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_char(char c, t_data_game *data_game)
{
	if (c != '1' && c != '0' && c != 'S' && c != 'W' && c != 'N' && c != 'E'
		&& c != ' ')
		return (-1);
	if (c == 'S' || c == 'W' || c == 'N' || c == 'E')
		data_game->flag.player_flag++;
	if (data_game->flag.player_flag > 1)
		return (-1);
	return (0);
}

int	check_space(char **map, int i, int j, int len)
{
	if (j < len - 1 && (map[i][j + 1] != '1' && map[i][j + 1] != ' '))
		return (-1);
	if (j > 0 && map[i][j - 1] && (map[i][j - 1] != '1' && map[i][j
			- 1] != ' '))
		return (-1);
	if ((map[i + 1][j] != '1' && map[i + 1][j] != ' '))
		return (-1);
	if (i > 0 && (map[i - 1][j] != '1' && map[i - 1][j] != ' '))
		return (-1);
	return (0);
}

int	check_view_side(char **map, int i, int j, int len)
{
	if (i == 0 && (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N'
			|| map[i][j] == 'W' || map[i][j] == 'E'))
		return (-1);
	if (map[i][len - 1] == '0' || map[i][len - 1] == 'S' || map[i][len
		- 1] == 'N' || map[i][len - 1] == 'W' || map[i][len - 1] == 'E')
		return (-1);
	if (j == 0 && (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N'
			|| map[i][j] == 'W' || map[i][j] == 'E'))
		return (-1);
	return (0);
}

int	check_zero(int i, int j, char **map)
{
	int	len;

	len = ft_strlen(map[i]);
	if (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N'
		|| map[i][j] == 'W' || map[i][j] == 'E')
	{
		if (check_view_side(map, i, j, len) == -1)
			return (-1);
	}
	if (map[i][j] == ' ')
	{
		if (check_space(map, i, j, len) == -1)
			return (-1);
	}
	if (map[i + 1] == NULL)
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (-1);
	}
	return (0);
}
