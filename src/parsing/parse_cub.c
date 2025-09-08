/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:45:59 by yannis            #+#    #+#             */
/*   Updated: 2025/09/08 14:08:31 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	walls_ceil_floor(char *line, t_data_game **data_game)
{
	if (add_wall(line, data_game) == -1)
		return (-1);
	if (add_color(line, data_game) == -1)
		return (-1);
	return (0);
}

static int	parse_line(char *line, t_data_game **data_game)
{
	if (check_flag(&(*data_game)->flag) == -1 && line_isdigit(line) == 1)
		return (-1);
	if ((*data_game)->map_data.height == 0
		&& check_flag(&(*data_game)->flag) == 1 && line[0] == '\n')
		return (1);
	if (check_flag(&(*data_game)->flag) == 1)
		(*data_game)->map_data.height++;
	if (line[0] != '\n')
		line = str_trim_nl(line);
	if (walls_ceil_floor(line, data_game) == -1)
		return (-1);
	return (0);
}

static int	parse_lines(int fd, t_data_game **data_game)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line)
	{
		ret = parse_line(line, data_game);
		if (ret == -1)
		{
			free(line);
			return (-1);
		}
		if (ret == 1)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	check_file(char *file, t_data_game **data_game)
{
	int	fd;
	int	ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = parse_lines(fd, data_game);
	close(fd);
	if (ret == -1)
		return (-1);
	if (check_flag(&(*data_game)->flag) == -1)
		return (-1);
	if ((*data_game)->count_walls != 4)
		return (-1);
	return (0);
}
