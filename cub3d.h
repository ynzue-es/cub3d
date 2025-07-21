/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:33:21 by yannis            #+#    #+#             */
/*   Updated: 2025/07/21 15:25:33 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>

typedef struct s_wall
{
	char			*direction;
	char			*texure_file;
}					t_wall;

typedef struct s_ceil_floor_colors
{
	int				ceil[3];
	int				floor[3];
}					t_ceil_floor;

typedef struct s_map_data
{
	int				width;
	int				height;
}					t_map_data;

typedef struct s_data_game
{
	t_wall			all_wall[4];
	int				count_walls;
	t_ceil_floor	ceil_floor;
	t_map_data		map_data;

}					t_data_game;

/*
 * utils
 */

int					check_ext(char *str);

/*
 * parsing
 */

int					check_file(char *file, t_data_game *data_game);

/*
 * init
 */

int					init_data_game(t_data_game *data_game);