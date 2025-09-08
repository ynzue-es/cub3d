/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:40:10 by yannis            #+#    #+#             */
/*   Updated: 2025/09/08 10:31:51 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 3)
		return (-1);
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_color(char letter, t_data_game **data_game, char *l, int i)
{
	if (letter == 'F')
	{
		if (add_tab_ceil_floor(l + i + 1, (*data_game)->ceil_floor.floor) == -1)
			return (-1);
		(*data_game)->flag.floor_flag++;
	}
	else if (letter == 'C')
	{
		if (add_tab_ceil_floor(l + i + 1, (*data_game)->ceil_floor.ceil) == -1)
			return (-1);
		(*data_game)->flag.ceil_flag++;
	}
	return (0);
}

int	add_color(char *line, t_data_game **data_game)
{
	char	letter;
	int		i;

	i = 0;
	letter = 0;
	while (line[i] == ' ' && line[i] != 'F' && line[i] != 'C')
		i++;
	if (line[i] == 'F' || line[i] == 'C')
	{
		if (line[i + 1] != ' ')
			return (-1);
		letter = line[i];
	}
	if (init_color(letter, data_game, line, i) == -1)
		return (-1);
	return (0);
}
