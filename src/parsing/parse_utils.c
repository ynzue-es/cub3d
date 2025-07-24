/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:33:32 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/24 13:29:59 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


int check_split(char **split)
{
	int i;
	int j;
	int count;
	
	count = 0;
	i = 0;
	j = 0;
	while(split[count])
		count++;
	if(count != 3)
		return (-1);
	while(split[j])
	{
		if(check_digit(split[j]) == -1)
		{
			return (-1);
		}
		j++;
	}
	return (0);
		
}

int check_convert(int convert)
{
	if(convert < 0)
		return (-1);
	if(convert > 255)
		return (-1);
	return (0);
}

int add_tab_floor(char *color,t_data_game *data_game)
{
	char **new_split;
	int convert;
	
	new_split = ft_split(color,',');
	if(check_split(new_split) == -1)
		return (-1);
	convert = ft_atoi(new_split[0]);
	if(check_convert(convert) == -1)
		return (-1);
	data_game->ceil_floor.floor[0] = convert;
	convert = ft_atoi(new_split[1]);
	if(check_convert(convert) == -1)
		return (-1);
	data_game->ceil_floor.floor[1] = convert; 
	convert = ft_atoi(new_split[2]);
	if(check_convert(convert) == -1)
		return (-1);
	data_game->ceil_floor.floor[2] = convert;
	return (0);
}
int add_tab_ceil(char *color,t_data_game *data_game)
{
	char **new_split;
	int convert;
	
	new_split = ft_split(color,',');
	if(check_split(new_split) == -1)
		return (-1);
	convert = ft_atoi(new_split[0]);
	if(check_convert(convert) == -1)
		return (-1);
	data_game->ceil_floor.ceil[0] = convert;
	convert = ft_atoi(new_split[1]);
	if(check_convert(convert) == -1)
		return (-1);
	data_game->ceil_floor.ceil[1] = convert; 
	convert = ft_atoi(new_split[2]);
	if(check_convert(convert) == -1)
		return (-1);
	data_game->ceil_floor.ceil[2] = convert;
	return (0);
}
int	check_flag(t_flag *flag)
{
	if(flag->ceil_flag != 1)
		return (-1);
	if(flag->floor_flag != 1)
		return (-1);
	if(flag->north_flag != 1)
		return (-1);
	if(flag->south_flag != 1)
		return (-1);
	if(flag->west_flag != 1)
		return (-1);
	if(flag->east_flag != 1)
		return (-1);
	return (1);
}
