/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:45:59 by yannis            #+#    #+#             */
/*   Updated: 2025/07/25 09:41:49 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	add_wall(char *direction, char *texture_file,
		t_data_game *data_game, t_flag *flag)
{
	if (ft_strncmp(direction, "NO", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[0].direction = direction;
		data_game->all_wall[0].texure_file = texture_file;
		flag->north_flag++;
		data_game->count_walls++;
	}
	else if (ft_strncmp(direction, "SO", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[1].direction = direction;
		data_game->all_wall[1].texure_file = texture_file;
		flag->south_flag++;
		data_game->count_walls++;
	}
	else if (ft_strncmp(direction, "WE", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[2].direction = direction;
		data_game->all_wall[2].texure_file = texture_file;
		flag->west_flag++;
		data_game->count_walls++;
	}
	else if (ft_strncmp(direction, "EA", 2) == 0 && ft_strlen(direction) == 2)
	{
		data_game->all_wall[3].direction = direction;
		data_game->all_wall[3].texure_file = texture_file;
		flag->east_flag++;
		data_game->count_walls++;
	}
	return (0);
}

int check_digit(char *str)
{
	int i;
	
	i = 0;
	
	if(ft_strlen(str) > 3)
		return (-1);
	while(str[i] && str[i] != '\n')
	{
		if(ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}


static int add_color(char *floor_or_ceil,char *color,t_data_game *data_game, t_flag *flag)
{
	if(ft_strncmp(floor_or_ceil,"F", 1) == 0 && ft_strlen(floor_or_ceil) == 1)
	{
		if(add_tab_ceil_floor(color, data_game->ceil_floor.floor) == -1)
			return (-1);
		flag->floor_flag++;
	}
	else if(ft_strncmp(floor_or_ceil, "C", 1) == 0 && ft_strlen(floor_or_ceil) == 1)
	{
		if(add_tab_ceil_floor(color,data_game->ceil_floor.ceil) == -1)
			return (-1);
		flag->ceil_flag++;
	}
	return (0);
}
static int	walls_ceil_floor(char *line, t_data_game *data_game, t_flag *flag)
{
	char	**spl;

	spl = ft_split(line, ' ');
	if (!spl)
		return (-1);
	if(add_wall(spl[0], spl[1], data_game, flag) == -1)
	return (free_split(spl), -1);
	if(add_color(spl[0],spl[1],data_game, flag) == -1)
		return (free_split(spl), -1);
	free_split(spl);
	return (0);
}

int	check_file(char *file, t_data_game *data_game,t_flag *flag)
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
		if (data_game->map_data.height == 0 && check_flag(flag) == 1 && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if(check_flag(flag) == 1)
			data_game->map_data.height++;
		if(line[0] != '\n')
			line = str_trim_nl(line);
		if(walls_ceil_floor(line, data_game,flag) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if(check_flag(flag) == -1)
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
