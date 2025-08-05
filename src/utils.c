/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:41:47 by yannis            #+#    #+#             */
/*   Updated: 2025/08/05 10:35:38 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	check_ext(char *str)
// {
// 	int	len;

// 	len = ft_strlen(str);
// 	if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c'
// 		&& str[len - 4] == '.')
// 		return (1);
// 	else
// 		return (-1);
// }

int	check_ext(char *str, char *extension)
{
	int	len;
	int len_extension;

	len_extension = ft_strlen(extension); 
	len = ft_strlen(str);
	
	if (str[len - 1] == extension[len_extension - 1] && str[len - 2] == extension[len_extension - 2] && str[len - 3] == extension[len_extension - 3]
		&& str[len - 4] == extension[len_extension - 4])
		return (1);
	else
		return (-1);
}
