/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:16:53 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/08 13:04:17 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	file_texture_no(t_data_game **data_game, char **spl)
{
	
	(*data_game)->all_wall[0].direction = spl[0];
	if (check_ext(spl[1], ".xpm") == -1)
	{
		ft_putendl_fd("Usage : ./cub3d filename.xpm", 2);
		free_split(spl);
		return (-1);
	
	}
	(*data_game)->all_wall[0].texture_file = ft_strndup(spl[1],
			ft_strlen(spl[1]));
	if(!(*data_game)->all_wall[0].texture_file)
	{
		free_split(spl);
		return (-1);
	}
	(*data_game)->flag.north_flag++;
	(*data_game)->count_walls++;
	return (0);
}

int	file_texture_so(t_data_game **data_game, char **spl)
{

	(*data_game)->all_wall[1].direction = spl[0];
	if (check_ext(spl[1], ".xpm") == -1)
	{
		ft_putendl_fd("Usage : ./cub3d filename.xpm", 2);
		free_split(spl);
		return (-1);
	}
	(*data_game)->all_wall[1].texture_file = ft_strndup(spl[1],
			ft_strlen(spl[1]));
	if(!(*data_game)->all_wall[1].texture_file)
	{
		free_split(spl);
		return (-1);
	}
	(*data_game)->flag.south_flag++;
	(*data_game)->count_walls++;
	return (0);
}

int	file_texture_we(t_data_game **data_game, char **spl)
{
	(*data_game)->all_wall[2].direction = spl[0];
	if (check_ext(spl[1], ".xpm") == -1)
	{
		ft_putendl_fd("Usage : ./cub3d filename.xpm", 2);
		free_split(spl);
		return (-1);
	}
	(*data_game)->all_wall[2].texture_file = ft_strndup(spl[1],
			ft_strlen(spl[1]));
	if(!(*data_game)->all_wall[2].texture_file)
	{
		free_split(spl);
		return (-1);
	}
	(*data_game)->flag.west_flag++;
	(*data_game)->count_walls++;
	return (0);
}

int	file_texture_ea(t_data_game **data_game, char **spl)
{
	(*data_game)->all_wall[3].direction = spl[0];
	if (check_ext(spl[1], ".xpm") == -1)
	{
		ft_putendl_fd("Usage : ./cub3d filename.xpm", 2);
		free_split(spl);
		return (-1);
	}
	(*data_game)->all_wall[3].texture_file = ft_strndup(spl[1],
			ft_strlen(spl[1]));
	if(!(*data_game)->all_wall[3].texture_file)
	{
		free_split(spl);
		return (-1);
	}
	(*data_game)->flag.east_flag++;
	(*data_game)->count_walls++;
	return (0);
}

int	add_wall(char *line, t_data_game **data_game)
{
	char	**spl;
	int		result;

	result = 0;
	spl = ft_split(line, ' ');
	if (!spl)
		return (-1);
	if (ft_strncmp(spl[0], "NO", 2) == 0 && ft_strlen(spl[0]) == 2)
		result = file_texture_no(data_game, spl);
	else if (ft_strncmp(spl[0], "SO", 2) == 0 && ft_strlen(spl[0]) == 2)
		result = file_texture_so(data_game, spl);
	else if (ft_strncmp(spl[0], "WE", 2) == 0 && ft_strlen(spl[0]) == 2)
		result = file_texture_we(data_game, spl);
	else if (ft_strncmp(spl[0], "EA", 2) == 0 && ft_strlen(spl[0]) == 2)
		result = file_texture_ea(data_game, spl);
	free_split(spl);
	if (result == -1)
		return (-1);
	return (0);
}
