/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:58:17 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/05 10:43:24 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_char(char c, t_data_game *data_game)
{
	if (c != '1' && c != '0' && c != 'S' && c != 'W' && c != 'N' && c != 'E'
		&& c != ' ')
		return (-1);
	if (c == 'S' || c == 'W' || c == 'N' || c == 'E')
		data_game->flag.player_flag++;
	if (data_game->flag.player_flag > 1)
		return (-1);
	return (0);
}
int	check_zero(int i, int j, char **map)
{
	int	len;

	len = ft_strlen(map[i]);
	if (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'|| map[i][j] == 'E')
	{
		if (i == 0 && (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'|| map[i][j] == 'E'))
            return (-1);
		if (map[i][len - 1] == '0' || map[i][len - 1] == 'S' || map[i][len - 1] == 'N' || map[i][len - 1] == 'W'|| map[i][len - 1] == 'E')
			return (-1);
        if(j == 0 && (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N'|| map[i][j] == 'W'|| map[i][j] == 'E'))
            return (-1);
	}
	if (map[i][j] == ' ')
	{
		if (j < len - 1 && (map[i][j + 1] != '1' && map[i][j + 1] != ' '))
			return (-1);
		if (j > 0 && map[i][j - 1] && (map[i][j - 1] != '1' && map[i][j
				- 1] != ' '))
			return (-1);
		if ((map[i + 1][j] != '1' && map[i + 1][j] != ' '))
			return (-1);
		if (i > 0 && (map[i - 1][j] != '1' && map[i - 1][j] != ' '))
			return (-1);
	}
	if (map[i + 1] == NULL)
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (-1);
	}
	return (0);
}
void	clean_map(t_data_game *data_game)
{
	int	i;

	i = data_game->map_data.height - 1;
	while (data_game->map_data.map[i][0] == '\n')
	{
		free(data_game->map_data.map[i]);
		i--;
	}
	data_game->map_data.map[i + 1] = NULL;
}
int	check_map(t_data_game *data_game)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	clean_map(data_game);
	map = data_game->map_data.map;
	while (map[i])
	{
		j = 0;
		if (map[i][0] == '\n')
			return (-1);
		while (map[i][j])
		{
			if (check_char(map[i][j], data_game) == -1)
				return (-1);
			if (check_zero(i, j, map) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (data_game->flag.player_flag == 0)
		return (-1);
	return (0);
}
int	malloc_map(t_data_game *data_game)
{
	int	j;

	if (data_game->map_data.height <= 2)
		return (-1);
	data_game->map_data.map = malloc(sizeof(char *)
			* (data_game->map_data.height + 1));
	if (!data_game->map_data.map)
		return (-1);
	j = 0;
	while (j < data_game->map_data.height)
	{
		data_game->map_data.map[j] = malloc(1);
		if (!data_game->map_data.map[j])
			return (free_split(data_game->map_data.map), -1);
		data_game->map_data.map[j][0] = 0;
		j++;
	}
	return (0);
}

int	process_map_line(char *line, t_data_game *data_game, int *i)
{
	char	*temp;

	temp = data_game->map_data.map[*i];
	data_game->map_data.map[*i] = ft_strjoin(temp, line);
	if (!data_game->map_data.map[*i])
	{
		free_split(data_game->map_data.map);
		return (free(line), free(temp), -1);
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
