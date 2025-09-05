/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:33:32 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/05 10:35:38 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*clear_str(char *line)
{
	char	*new_str;
	int		i;
	int		j;
	int		count;

	count = 0;
	new_str = NULL;
	j = 0;
	i = 0;
	count = size_clear_str(line);
	new_str = malloc(count + 1);
	if (!new_str)
		return (NULL);
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		new_str[j++] = line[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	check_all_convert(int *ceil_floor, char **new_split)
{
	int	convert;

	convert = ft_atoi(new_split[0]);
	if (check_convert(convert) == -1)
		return (free_split(new_split), -1);
	ceil_floor[0] = convert;
	convert = ft_atoi(new_split[1]);
	if (check_convert(convert) == -1)
		return (free_split(new_split), -1);
	ceil_floor[1] = convert;
	convert = ft_atoi(new_split[2]);
	if (check_convert(convert) == -1)
		return (free_split(new_split), -1);
	ceil_floor[2] = convert;
	return (0);
}

int	add_tab_ceil_floor(char *line, int *ceil_floor)
{
	char	**new_split;
	char	*new_str;

	new_str = clear_str(line);
	if (!new_str)
		return (-1);
	new_split = ft_split(new_str, ',');
	if (!new_split)
		return (-1);
	if (check_split(new_split) == -1)
		return (free_split(new_split), -1);
	check_all_convert(ceil_floor, new_split);
	free_split(new_split);
	free(new_str);
	return (0);
}

int	check_flag(t_flag *flag)
{
	if (flag->ceil_flag != 1)
		return (-1);
	if (flag->floor_flag != 1)
		return (-1);
	if (flag->north_flag != 1)
		return (-1);
	if (flag->south_flag != 1)
		return (-1);
	if (flag->west_flag != 1)
		return (-1);
	if (flag->east_flag != 1)
		return (-1);
	return (1);
}
