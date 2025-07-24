/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:41:47 by yannis            #+#    #+#             */
/*   Updated: 2025/07/24 14:11:13 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen_fd(char *file, t_data_game *data_game)
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
		data_game->len_fd++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
int	check_ext(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c'
		&& str[len - 4] == '.')
		return (1);
	else
		return (0);
}
