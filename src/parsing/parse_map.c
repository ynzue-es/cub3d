/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:58:17 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/24 11:26:00 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	malloc_map(t_data_game *data_game)
{
	int	j;

	data_game->map_data.map = malloc(sizeof(char *) * data_game->map_data.height);
	if (!data_game->map_data.map)
		return (-1);
	j = 0;
	while (j < data_game->map_data.height)
	{
		data_game->map_data.map[j] = malloc(1);
		data_game->map_data.map[j][0] = 0;
		j++;
	}
	return (0);
}
int	init_map(char *file, t_data_game *data_game)
{
	int fd;
	char *line;
	int count;
	int i;
	char *temp;

	malloc_map(data_game);
	i = 0;
	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line)
	{
		if (line[0] != '\n')
		{
			count++;
			line = str_trim_nl(line);
		}
		if (count > 6)
		{
			if (!line)
				break ;
			temp = data_game->map_data.map[i];
			data_game->map_data.map[i] = ft_strjoin(temp, line);
			if (!data_game->map_data.map[i])
			{
				free_split(data_game->map_data.map);
				free(line);
				free(temp);
				return (-1);
			}
			free(temp);
			count++;
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	data_game->map_data.map[i] = NULL;
	close(fd);
	return (0);
}
