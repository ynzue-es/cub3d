/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:45:59 by yannis            #+#    #+#             */
/*   Updated: 2025/09/04 14:42:56 by engiusep         ###   ########.fr       */
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

int	init_color(char letter, t_data_game **data_game, char *line, int i)
{
	if (letter == 'F')
	{
		if (add_tab_ceil_floor(line + i + 1, (*data_game)->ceil_floor.floor) == -1)
			return (-1);
		(*data_game)->flag.floor_flag++;
	}
	else if (letter == 'C')
	{
		if (add_tab_ceil_floor(line + i + 1, (*data_game)->ceil_floor.ceil) ==
			-1)
			return (-1);
		(*data_game)->flag.ceil_flag++;
	}
	return (0);
}

static int	add_color(char *line, t_data_game **data_game)
{
	char	**spl;
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
	spl = ft_split(line + i + 1, ',');
	if (!spl)
		return (-1);
	if (init_color(letter, data_game, line, i) == -1)
		return (-1);
	free_split(spl);
	return (0);
}

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
