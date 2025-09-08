/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:18:12 by yannis            #+#    #+#             */
/*   Updated: 2025/09/08 12:44:32 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_forward(t_data_game *data, float speed)
{
	float	new_x;
	float	new_y;

	new_x = data->player_pos.player_pos_x + cosf(data->player_pos.player_angle)
		* speed;
	new_y = data->player_pos.player_pos_y + sinf(data->player_pos.player_angle)
		* speed;
	if (data->map_data.map[(int)new_y][(int)new_x] != '1')
	{
		data->player_pos.player_pos_x = new_x;
		data->player_pos.player_pos_y = new_y;
	}
}

void	move_side(t_data_game *data, float speed)
{
	float	new_x;
	float	new_y;

	new_x = data->player_pos.player_pos_x - sinf(data->player_pos.player_angle)
		* speed;
	new_y = data->player_pos.player_pos_y + cosf(data->player_pos.player_angle)
		* speed;
	if (data->map_data.map[(int)new_y][(int)new_x] != '1')
	{
		data->player_pos.player_pos_x = new_x;
		data->player_pos.player_pos_y = new_y;
	}
}

void	rotate_player(t_data_game *data, float angle)
{
	data->player_pos.player_angle += angle;
}

void	exit_game(t_data_game *g)
{
	free_split(g->map_data.map);
	free_texture(g);
	mlx_destroy_image(g->data_mlx.mlx_ptr, g->data_pixel.img_ptr);
	mlx_destroy_window(g->data_mlx.mlx_ptr, g->data_mlx.window_ptr);
	mlx_destroy_display(g->data_mlx.mlx_ptr);
	free(g->data_mlx.mlx_ptr);
	free(g);
	exit(1);
}

int	key_code(int key, t_data_game *data_game)
{
	if (key == 119)
		move_forward(data_game, 0.5);
	else if (key == 115)
		move_forward(data_game, -0.5);
	else if (key == 100)
		move_side(data_game, 0.5);
	else if (key == 97)
		move_side(data_game, -0.5);
	else if (key == 65363)
		rotate_player(data_game, 0.1);
	else if (key == 65361)
		rotate_player(data_game, -0.1);
	else if (key == 65307)
		exit_game(data_game);
	game_view(data_game);
	return (0);
}
