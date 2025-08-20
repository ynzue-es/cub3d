/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:10:21 by engiusep          #+#    #+#             */
/*   Updated: 2025/08/20 15:04:02 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


void	my_mlx_pixel_put(t_data_pixel *data_pixel, int x, int y, int color)
{ 
	char	*dst;
	if (x < 0 || y < 0 || x >= 2000 || y >= 1090)
		return ;
	dst = data_pixel->addr + (y * data_pixel->line_length + x * (data_pixel->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int	key_code(int key, t_data_game *data)
{
	float new_x;
	float new_y;
	if (key == 119)
	{
		new_x = data->player_pos.player_pos_x + cos(data->player_pos.player_angle) * 0.5;
		new_y = data->player_pos.player_pos_y + sin(data->player_pos.player_angle) * 0.5;
		if(data->map_data.map[(int)new_y][(int)new_x] != '1')
		{
			data->player_pos.player_pos_x = new_x;
            data->player_pos.player_pos_y = new_y;
			
		}
	}
	else if(key == 115)
	{
		new_x = data->player_pos.player_pos_x + cos(data->player_pos.player_angle) * -0.5;
		new_y = data->player_pos.player_pos_y + sin(data->player_pos.player_angle) * -0.5;
		if(data->map_data.map[(int)new_y][(int)new_x] != '1')
		{
			data->player_pos.player_pos_x = new_x;
            data->player_pos.player_pos_y = new_y;
		}
	}
	else if (key == 100)
		data->player_pos.player_angle += 0.1;
	else if (key == 97)
		data->player_pos.player_angle -= 0.1;
	else if(key == 65307)
		exit(1);
	//mlx_clear_window(data->data_mlx->mlx_ptr,data->data_mlx->window_ptr);
	put_segment(data->data_mlx, data,data->data_pixel);
	printf("key code = %d\n", key);
	return (0);
}
int	put_wall(t_data_game *data ,int ray_x,int ray_y)
{
	void *wall;
	int h;
	int w;

	wall = mlx_xpm_file_to_image(data->data_mlx->mlx_ptr,"wall.xpm", &w, &h);
	mlx_put_image_to_window(data->data_mlx->mlx_ptr,data->data_mlx->window_ptr,wall,ray_x,ray_y);
	return (0);
}
void draw_background(t_data_pixel *data_pixel)
{
    for (int y = 0; y < 1090; y++)
    {
        int color = (y < 545) ? 0x87CEEB : 0x228B22;
        for (int x = 0; x < 2000; x++)
            my_mlx_pixel_put(data_pixel, x, y, color);
    }
}

int	put_wall_segement(t_data_game *data, int i)
{
	int y;
	int vx;
	int vy;
	int dist;
	
	vx = data->ray_data.ray_x - (data->player_pos.player_pos_x * 16 + 8);
	vy = data->ray_data.ray_y - (data->player_pos.player_pos_y * 16 + 8);
	dist = sqrtf(pow(vx, 2) + pow(vy, 2));

	int wall_height = (int)(1090 / dist) * 16 + 8;
	int draw_start = (1090 / 2) - (wall_height / 2);
	int draw_end = (1090 / 2) + (wall_height / 2);

	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(data->data_pixel, i, y, 0xFF0000);
		y++;
	}
	return (0);
	
}

void	ray_cast(t_data_game *data, float ray_angle,t_data_pixel *data_pixel, int i)
{
	
	(void)i;
	data->ray_data.ray_x = data->player_pos.player_pos_x * 16 + 8;
	data->ray_data.ray_y = data->player_pos.player_pos_y * 16 + 8;
	
	data->ray_data.ray_dir_x =  cos(ray_angle);
	data->ray_data.ray_dir_y =  sin(ray_angle);
	(void)data_pixel;
	while (1)
	{
		data->ray_data.map_x = (int)(data->ray_data.ray_x / 16);
		data->ray_data.map_y = (int)(data->ray_data.ray_y / 16);
		if (data->map_data.map[data->ray_data.map_y][data->ray_data.map_x] == '1')
		{
			break ;
		}
		my_mlx_pixel_put(data_pixel,(int)data->ray_data.ray_x,(int)data->ray_data.ray_y,0xFF0000);
		data->ray_data.ray_x += data->ray_data.ray_dir_x * 1;
		data->ray_data.ray_y += data->ray_data.ray_dir_y * 1;
	}
	put_wall_segement(data, i);
}

int	put_segment(t_window *data_mlx, t_data_game *data_game,t_data_pixel *data_pixel)
{
	int i;
	int j;
	int x;
	int y;

	j = 0;
	i = 0;
	x = 0;
	y = 0;
	while (data_game->map_data.map[i])
	{
		j = 0;
		while (data_game->map_data.map[i][j])
		{
			y = 0;
			if (data_game->map_data.map[i][j] == '1')
			{
				while (y < 16)
				{
					x = 0;
					while (x < 16)
					{
						
						my_mlx_pixel_put(data_pixel,j * 16 + x,i *16 + y,0xFFFFFF);
						x++;
					}
					y++;
				}
			}
			if (data_game->map_data.map[i][j] == '0')
			{
				y = 0;
				while (y < 16)
				{
					x = 0;
					while (x < 16)
					{
						my_mlx_pixel_put(data_pixel,j * 16 + x,i *16 + y,0xF00FFF);
						x++;
					}
					y++;
				}
			}
			if (data_game->map_data.map[i][j] == 'N')
			{
				
				if(data_game->flag.fisrt_pos_flag == 0)
				{
					data_game->player_pos.player_pos_x = j;
					data_game->player_pos.player_pos_y = i;
					data_game->player_pos.player_angle = -M_PI / 2;
					data_game->flag.fisrt_pos_flag = 1;
					data_game->map_data.map[i][j] = '0';
				}
			}
			j++;
		}
		i++;
	}
	
	y = 0;
    while (y < 16)
    {
        x = 0;
        while (x < 16)
        {
			my_mlx_pixel_put(data_pixel,(int)(data_game->player_pos.player_pos_x * 16) + x,(int)(data_game->player_pos.player_pos_y * 16) + y, 0x000066);
            x++;
        }
        y++;
    }
	float fov = M_PI / 3;
	int num_rays = 2000;
	float ray_angle;
	i = 0;
	draw_background(data_pixel);
	while (i < num_rays)
	{
		ray_angle = data_game->player_pos.player_angle - fov/2 + (fov * i / num_rays);
		ray_cast(data_game, ray_angle, data_pixel, i);
		i++;
	}
	
	mlx_put_image_to_window(data_mlx->mlx_ptr,data_mlx->window_ptr,data_pixel->img_ptr,0,0);
	return (0);
}
