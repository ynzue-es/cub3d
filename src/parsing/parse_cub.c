/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:45:59 by yannis            #+#    #+#             */
/*   Updated: 2025/08/04 13:13:58 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	add_wall(char *line, t_data_game *data_game, t_flag *flag)
{
	char	**spl;

	spl = ft_split(line, ' ');
	if (!spl)
		return (-1);
	if (ft_strncmp(spl[0], "NO", 2) == 0 && ft_strlen(spl[0]) == 2)
	{
		data_game->all_wall[0].direction = spl[0];
		data_game->all_wall[0].texure_file = spl[1];
		flag->north_flag++;
		data_game->count_walls++;
	}
	else if (ft_strncmp(spl[0], "SO", 2) == 0 && ft_strlen(spl[0]) == 2)
	{
		data_game->all_wall[1].direction = spl[0];
		data_game->all_wall[1].texure_file = spl[1];
		flag->south_flag++;
		data_game->count_walls++;
	}
	else if (ft_strncmp(spl[0], "WE", 2) == 0 && ft_strlen(spl[0]) == 2)
	{
		data_game->all_wall[2].direction = spl[0];
		data_game->all_wall[2].texure_file = spl[1];
		flag->west_flag++;
		data_game->count_walls++;
	}
	else if (ft_strncmp(spl[0], "EA", 2) == 0 && ft_strlen(spl[0]) == 2)
	{
		data_game->all_wall[3].direction = spl[0];
		data_game->all_wall[3].texure_file = spl[1];
		flag->east_flag++;
		data_game->count_walls++;
	}
	free_split(spl);
	return (0);
}

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

static int	add_color(char *line, t_data_game *data_game,
		t_flag *flag)
{
	char **spl;
	char lettre;
	int i;
	int j;

	j = 0;
	i = 0;
	lettre = 0;
	
	while(line[i] == ' ' && line[i] != 'F' && line[i] != 'C')
		i++;
	if(line[i] == 'F' || line[i] == 'C')
	{
		if(line[i + 1] != ' ')
			return (-1);
		lettre = line[i];
	}
	spl = ft_split(line + i + 1, ',');
	if(!spl)
		return (-1);
	if (lettre == 'F')
	{
		if (add_tab_ceil_floor(line + i + 1, data_game->ceil_floor.floor) == -1)
			return (-1);
		flag->floor_flag++;
	}
	else if (lettre == 'C')
	{
		if (add_tab_ceil_floor(line + i + 1, data_game->ceil_floor.ceil) == -1)
			return (-1);
		flag->ceil_flag++;
	}
	free_split(spl);
	return (0);
}
static int	walls_ceil_floor(char *line, t_data_game *data_game, t_flag *flag)
{
	if (add_wall(line, data_game, flag) == -1)
		return (-1);
	if (add_color(line, data_game, flag) == -1)
		return (-1);
	return (0);
}

int	check_file(char *file, t_data_game *data_game, t_flag *flag)
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
		if (check_flag(flag) == -1 && line_isdigit(line) == 1)
		{
			return (-1);
		}
		if (data_game->map_data.height == 0 && check_flag(flag) == 1
			&& line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (check_flag(flag) == 1)
			data_game->map_data.height++;
		if (line[0] != '\n')
			line = str_trim_nl(line);
		if (walls_ceil_floor(line, data_game, flag) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (check_flag(flag) == -1)
		return (-1);
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
