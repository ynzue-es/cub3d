/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:41:47 by yannis            #+#    #+#             */
/*   Updated: 2025/09/08 14:15:15 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_ext(char *str, char *extension)
{
	int	len;
	int	len_extension;

	len_extension = ft_strlen(extension);
	len = ft_strlen(str);
	if (str[len - 1] == extension[len_extension - 1]
		&& str[len - 2] == extension[len_extension - 2]
		&& str[len - 3] == extension[len_extension - 3]
		&& str[len - 4] == extension[len_extension - 4])
		return (1);
	else
		return (-1);
}

int free_texture(t_data_game *g)
{
    int j;

	j = 0;
    while (j < 4)
    {		
		if (g->all_wall[j].texture_file)
        {
			free(g->all_wall[j].texture_file);
            g->all_wall[j].texture_file = NULL;
        }
		if (g->wall_t[j].img_ptr)
		{
			mlx_destroy_image(g->data_mlx.mlx_ptr, g->wall_t[j].img_ptr);
			g->wall_t[j].img_ptr = NULL;
			g->wall_t[j].addr = NULL; 
		}
		
        j++;
    }
    return (0);
}

