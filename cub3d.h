/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:33:21 by yannis            #+#    #+#             */
/*   Updated: 2025/07/25 08:22:12 by yannis           ###   ########.fr       */
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
	char			**map;
}					t_map_data;

typedef struct s_flag
{
	int				ceil_flag;
	int				floor_flag;
	int				north_flag;
	int				west_flag;
	int				south_flag;
	int				east_flag;

}					t_flag;

typedef struct s_data_game
{
	t_wall			all_wall[4];
	int				count_walls;
	t_ceil_floor	ceil_floor;
	t_flag			flag;
	t_map_data		map_data;

}					t_data_game;

/*
 * utils
 */
int					check_ext(char *str);

/*
 * parsing
 */
int					check_flag(t_flag *flag);
int					check_file(char *file, t_data_game *data_game,
						t_flag *flag);
int					add_tab_ceil_floor(char *color, int *ceil_floor);
int					check_convert(int convert);
int					check_split(char **split);
int					check_digit(char *str);
int					init_map(char *file, t_data_game *data_game);
/*
 * init
 */

int					init_data_game(t_data_game *data_game);
int					init_flag(t_flag *flag);
