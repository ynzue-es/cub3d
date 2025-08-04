/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:33:32 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/04 13:12:52 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


int check_split(char **split)
{
	int j;
	int count;
	
	count = 0;
	j = 0;
	while(split[count])
		count++;
	if(count != 3)
		return (-1);
	while(split[j])
	{
		if(check_digit(split[j]) == -1)
			return (-1);
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

char *clear_str(char *line)
{
	char *new_str;
	int i;
	int j;
	int count;

	count = 0;
	new_str = NULL;
	j = 0;
	i = 0;
	
	while(line[i])
	{
		if(line[i] == ' ')
			i++;
		count++;
		i++;
	}
	i = 0;
	new_str = malloc(count + 1);
	while(line[i])
	{
		if(line[i] == ' ')
		{
			i++;
			continue;
		}
		new_str[j] = line[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}
int add_tab_ceil_floor(char *line, int *ceil_floor)
{
	char **new_split;
	char *new_str;
	int convert;
	int i;

	i = 0;
	new_str = clear_str(line);
	new_split = ft_split(new_str,',');
	if (!new_split)
		return (-1);
	if(check_split(new_split) == -1)
		return (free_split(new_split), -1);
	convert = ft_atoi(new_split[0]);
	if(check_convert(convert) == -1)
		return (free_split(new_split), -1);
	ceil_floor[0] = convert;
	convert = ft_atoi(new_split[1]);
	if(check_convert(convert) == -1)
		return (free_split(new_split), -1);
	ceil_floor[1] = convert; 
	convert = ft_atoi(new_split[2]);
	if(check_convert(convert) == -1)
		return (free_split(new_split), -1);
	ceil_floor[2] = convert;
	free_split(new_split);
	free(new_str);
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
