/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:35:40 by yannis            #+#    #+#             */
/*   Updated: 2025/09/05 10:38:35 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_split(char **split)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (split[count])
		count++;
	if (count != 3)
		return (-1);
	while (split[j])
	{
		if (check_digit(split[j]) == -1)
			return (-1);
		j++;
	}
	return (0);
}

int	check_convert(int convert)
{
	if (convert < 0)
		return (-1);
	if (convert > 255)
		return (-1);
	return (0);
}

int	size_clear_str(char *line)
{
	int	i;
	int	count;

	// revoir count
	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		count++;
		i++;
	}
	return (count);
}
