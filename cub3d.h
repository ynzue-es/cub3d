/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:33:21 by yannis            #+#    #+#             */
/*   Updated: 2025/09/05 10:42:25 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

enum
{
	TEX_NORTH,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST
};

typedef struct s_wall
{
	char			*direction;
	char			*texure_file;
}					t_wall;

typedef struct s_data_pixel
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data_pixel;

typedef struct s_wall_draw
{
	int				wall_height;
	int				draw_start;
	int				draw_end;
}					t_wall_draw;

typedef struct s_wall_texture
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_wall_texture;

typedef struct s_tex_coords
{
	int				tex_id;
	t_wall_texture	*tex;
	int				tex_x;
	float			step;
	float			tex_pos_0;
}					t_tex_coords;

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
	void			*mlx_ptr;
	void			*window_ptr;
	int				width;
	int				height;
}					t_window;

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

}					t_flag;

typedef struct s_player_pos
{
	float			player_pos_x;
	float			player_pos_y;
	float			player_angle;
}					t_player_pos;

typedef struct s_ray_data
{
	float			ray_x;
	float			ray_y;
	int				map_x;
	int				map_y;
	float			ray_dir_x;
	float			ray_dir_y;
	float			deltaDistX;
	float			deltaDistY;
	float			sideDistX;
	float			sideDistY;
	int				hit_side;
	int				stepX;
	int				stepY;
	float			ray_angle;
}					t_ray_data;

typedef struct s_data_game
{
	t_wall			all_wall[4];
	int				count_walls;
	t_ceil_floor	ceil_floor;
	t_flag			flag;
	t_map_data		map_data;
	t_player_pos	player_pos;
	t_window		data_mlx;
	t_data_pixel	data_pixel;
	t_ray_data		ray_data;
	int				tile_size;
	t_wall_texture	wall_t[4];
	float			fov;
}					t_data_game;

/*
 * utils
 */
int					check_ext(char *str, char *extension);

/*
 * parsing
 */
int					check_flag(t_flag *flag);
int					check_file(char *file, t_data_game **data_game);
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

/*
 * game_view
 */
int					game_view(t_data_game *data_game);

/*
 * keyboard
 */
int					key_code(int key, t_data_game *data);

/*
 * pixel_display
 */
int					put_wall_segment(t_data_game *g, int x, float perpWallDist,
						int hit_side);
void				draw_background(t_data_game *data_game);

/*
 * ray_casting
 */
void				ray_cast(t_data_game *g, int i);
/*
 * display_minimap
 */
void				display_minimap(t_data_game *data_game,
						t_data_pixel *data_pixel);
void				my_mlx_pixel_put(t_data_pixel *data_pixel, int x, int y,
						int color);
int					add_wall(char *line, t_data_game **data_game);
int					malloc_map(t_data_game *data_game);
int					check_map(t_data_game *data_game);
int					check_char(char c, t_data_game *data_game);
int					check_zero(int i, int j, char **map);
int					init_mlx(t_data_game **g);
int					init_mlx_texture(t_data_game **g, int i);
int					switch_tab_int(t_data_game *data_game, int flag_ceil_floor);
float				hit_point_fraction(t_data_game *g, int hit_side,
						float perpWallDist);
void				draw_textured_column(t_data_game *g, int x, t_wall_draw *wd,
						t_tex_coords *tc);
float				projection_plane(t_data_game *g);
int					pick_tex_id(int hit_side, int step_x, int step_y);
int					size_clear_str(char *line);
int					add_color(char *line, t_data_game **data_game);