/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/09/04 13:00:29 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx(t_data_game **data_game)
{
	(*data_game)->data_mlx.mlx_ptr = mlx_init();
	if (!(*data_game)->data_mlx.mlx_ptr)
		return (1);
	(*data_game)->data_mlx.window_ptr = mlx_new_window((*data_game)->data_mlx.mlx_ptr,
			(*data_game)->data_mlx.width, (*data_game)->data_mlx.height,
			"cub3d");
	if (!(*data_game)->data_mlx.window_ptr)
		return (1);
	(*data_game)->data_pixel.img_ptr = mlx_new_image((*data_game)->data_mlx.mlx_ptr,
			(*data_game)->data_mlx.width, (*data_game)->data_mlx.height);
	if (!(*data_game)->data_pixel.img_ptr)
		return (1);
	(*data_game)->data_pixel.addr = mlx_get_data_addr((*data_game)->data_pixel.img_ptr,
			&(*data_game)->data_pixel.bits_per_pixel,
			&(*data_game)->data_pixel.line_length,
			&(*data_game)->data_pixel.endian);
	if (!(*data_game)->data_pixel.addr)
		return (1);
	return (0);
}

int	init_mlx_texture(t_data_game **data_game, int i)
{
	(*data_game)->wall_texture[i].img_ptr = mlx_xpm_file_to_image((*data_game)->data_mlx.mlx_ptr,
		(*data_game)->all_wall[i].texure_file, &(*data_game)->wall_texture[i].width, &(*data_game)->wall_texture[i].height);
	if(!(*data_game)->wall_texture[i].img_ptr)
		return (1);
	(*data_game)->wall_texture[i].addr = mlx_get_data_addr((*data_game)->wall_texture[i].img_ptr,
			&(*data_game)->wall_texture[i].bits_per_pixel,
			&(*data_game)->wall_texture[i].line_length,
			&(*data_game)->wall_texture[i].endian);
	if(!(*data_game)->wall_texture[i].addr)
		return (1);
	return (0);
}

static int	init_structs(t_data_game **data_game)
{
	*data_game = malloc(sizeof(t_data_game));
	if (!*data_game)
		return (1);
	return (0);
}

static int	init_map_and_flags(int argc, char **argv, t_data_game **data_game)
{
	if (argc != 2)
		return (free(*data_game), ft_putendl_fd("Usage : ./cub3d filename.cub",
				2), 1);
	if (check_ext(argv[1], ".cub") == -1)
		return (free(*data_game), ft_putendl_fd("Usage : ./cub3d filename.cub",
				2), 1);
	init_flag(&(*data_game)->flag);
	init_data_game(*data_game);
	if (check_file(argv[1], data_game) == -1)
	{
		ft_putendl_fd("Error", 2);
		free(*data_game);
		return (1);
	}
	if (init_map(argv[1], *data_game) == -1)
	{
		ft_putendl_fd("Error", 2);
		free(*data_game);
		return (1);
	}
	return (0);
}

int	init_game(int argc, char **argv, t_data_game **data_game)
{
	int i;

	i = 0;
	if (init_structs(data_game) != 0)
		return (1);
	if (init_map_and_flags(argc, argv, data_game) != 0)
		return (1);
	if (init_mlx(data_game) != 0)
		return (1);
	while (i < 4)
	{
		if (init_mlx_texture(data_game, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data_game	*data_game;

	if (init_game(argc, argv, &data_game) != 0)
		return (1);
	mlx_hook(data_game->data_mlx.window_ptr, KeyPress, KeyPressMask, key_code,
		data_game);
	game_view(data_game);
	//display_minimap(data_game,&data_game->data_pixel);
	mlx_loop(data_game->data_mlx.mlx_ptr);
	free_split(data_game->map_data.map);
	free(data_game);
	return (0);
}
