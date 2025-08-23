/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:41:47 by yannis            #+#    #+#             */
/*   Updated: 2025/08/23 15:22:47 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_ext(char *str, char *extension)
{
	int	len;
	int	len_extension;

	len_extension = ft_strlen(extension);
	len = ft_strlen(str);
	if (str[len - 1] == extension[len_extension - 1] && str[len
		- 2] == extension[len_extension - 2] && str[len
		- 3] == extension[len_extension - 3] && str[len
		- 4] == extension[len_extension - 4])
		return (1);
	else
		return (-1);
}
