/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:58:17 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/08 12:32:24 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	process_map_line(char *line, t_data_game *data_game, int *i)
{
	char	*temp;

	temp = data_game->map_data.map[*i];
	data_game->map_data.map[*i] = ft_strjoin(temp, line);
	if (!data_game->map_data.map[*i])
	{
		free_split(data_game->map_data.map);
		free(line);
		free(temp);
		return (-1);
	}
	free(temp);
	(*i)++;
	return (0);
}

int	handle_line(char *line, t_data_game *data_game, int *i, int *count)
{
	if (line[0] != '\n')
	{
		(*count)++;
		line = str_trim_nl(line);
	}
	if (*count > 6)
	{
		if (!line)
			return (-1);
		if (process_map_line(line, data_game, i) == -1)
			return (-1);
	}
	free(line);
	return (0);
}

int	read_map_lines(int fd, t_data_game *data_game)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line)
	{
		if (handle_line(line, data_game, &i, &count) == -1)
			return (-1);
		line = get_next_line(fd);
	}
	data_game->map_data.map[i] = NULL;
	return (0);
}

int	init_map(char *file, t_data_game *data_game)
{
	int	fd;

	if (malloc_map(data_game) == -1)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (read_map_lines(fd, data_game) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (check_map(data_game) == -1)
		return (-1);
	return (0);
}
