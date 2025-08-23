/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:18:12 by yannis            #+#    #+#             */
/*   Updated: 2025/08/23 14:17:14 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void move_forward(t_data_game *data, float speed)
{
	float new_x = data->player_pos.player_pos_x + cos(data->player_pos.player_angle) * speed;
	float new_y = data->player_pos.player_pos_y + sin(data->player_pos.player_angle) * speed;
	if (data->map_data.map[(int)new_y][(int)new_x] != '1')
	{
		data->player_pos.player_pos_x = new_x;
		data->player_pos.player_pos_y = new_y;
	}
}

void rotate_player(t_data_game *data, float angle)
{
	data->player_pos.player_angle += angle;
}

void exit_game(void)
{
	exit(1);
}

int key_code(int key, t_data_game *data)
{
	if (key == 122)
		move_forward(data, 0.5);
	else if (key == 115)
		move_forward(data, -0.5);
	else if (key == 100)
		rotate_player(data, 0.1);
	else if (key == 113)
		rotate_player(data, -0.1);
	else if (key == 65307)
		exit_game();
	game_view(data->data_mlx, data, data->data_pixel);
	printf("key code = %d\n", key);
	return (0);
}
