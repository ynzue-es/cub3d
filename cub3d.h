/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:33:21 by yannis            #+#    #+#             */
/*   Updated: 2025/08/20 13:12:20 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_wall
{
	char			*direction;
	char			*texure_file;
}					t_wall;

typedef struct s_data_pixel 
{
    void    *img_ptr;      
    char    *addr;         
    int     bits_per_pixel; 
    int     line_length;   
    int     endian;        
} t_data_pixel;

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

typedef struct s_window
{
	void *mlx_ptr;
	void *window_ptr;
}	t_window;

typedef struct s_flag
{
	int				ceil_flag;
	int				floor_flag;
	int				north_flag;
	int				west_flag;
	int				south_flag;
	int				east_flag;
	int				player_flag;
	int				fisrt_pos_flag;
	

}			t_flag;

typedef struct s_point
{
	int x;
	int y;
		}t_point;

typedef struct s_player_pos
{
	float player_pos_x;
	float player_pos_y;
	float player_angle;
}t_player_pos;

typedef struct s_segment
{
	t_point p1;
	t_point p2;	
}t_segment;


typedef struct s_ray_data
{
	float	ray_x;
	float	ray_y;
	int		map_x;
	int		map_y;
	float	ray_dir_x;
	float	ray_dir_y;
}			t_ray_data;

typedef struct s_data_game
{
	t_wall			all_wall[4];
	int				count_walls;
	t_ceil_floor	ceil_floor;
	t_flag			flag;
	t_map_data		map_data;
	t_player_pos	player_pos;
	t_window		*data_mlx;
	t_data_pixel    *data_pixel;
	t_ray_data		ray_data;
}					t_data_game;


/*
 * utils
 */
int					check_ext(char *str,char *extension);
int 				key_code(int key,t_data_game *data);


/*
 * parsing
 */
int					check_flag(t_flag *flag);
int					check_file(char *file, t_data_game *data_game,
						t_flag *flag);
int					add_tab_ceil_floor(char *line, int *ceil_floor);
int					check_convert(int convert);
int					check_split(char **split);
int					check_digit(char *str);
int					init_map(char *file, t_data_game *data_game);
/*
 * init
 */

int					init_data_game(t_data_game *data_game);
int					init_flag(t_flag *flag);
int 				init_data_pixel(t_data_pixel *data_pixel);

/*
 *raycasting
 */
int					put_segment(t_window *data_mlx,t_data_game *data_map,t_data_pixel *data_pixel);