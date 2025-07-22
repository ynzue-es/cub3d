/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:45:59 by yannis            #+#    #+#             */
/*   Updated: 2025/07/21 15:25:57 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	add_wall(char *direction, char *texture_file,
		t_data_game *data_game)
{
	if (ft_strncmp(direction, "NO", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[0].direction = direction;
		data_game->all_wall[0].texure_file = texture_file;
		data_game->count_walls++;
	}
	else if (ft_strncmp(direction, "SO", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[1].direction = direction;
		data_game->all_wall[1].texure_file = texture_file;
		data_game->count_walls++;
	}
	else if (ft_strncmp(direction, "WE", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[2].direction = direction;
		data_game->all_wall[2].texure_file = texture_file;
		data_game->count_walls++;
	}
	else if (ft_strncmp(direction, "EA", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[3].direction = direction;
		data_game->all_wall[3].texure_file = texture_file;
		data_game->count_walls++;
	}
	return (0);
}

static int	is_walls(char *line, t_data_game *data_game)
{
	char	**spl;

	spl = ft_split(line, ' ');
	if (!spl)
		return (-1);
	add_wall(spl[0], spl[1], data_game);
	return (0);
}

int	check_file(char *file, t_data_game *data_game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line)
	{
		is_walls(line, data_game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (data_game->count_walls != 4)
		return (-1);
	return (0);
}

// is_ceil_or_floorgit ()
// {

// }

// find_map()
// {

// }
