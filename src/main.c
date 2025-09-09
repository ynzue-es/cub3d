/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/09/09 10:47:04 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	init_structs(t_data_game **g)
{
	*g = ft_calloc(1, sizeof(t_data_game));
	if (!*g)
		return (1);
	return (0);
}

static int	init_map_and_flags(char **argv, t_data_game **g)
{
	init_flag(&(*g)->flag);
	init_data_game(*g);
	if (check_file(argv[1], g) == -1)
	{
		ft_putendl_fd("Error file in parsing", 2);
		return (1);
	}
	if (init_map(argv[1], *g) == -1)
	{
		ft_putendl_fd("Error file map", 2);
		if ((*g)->map_data.map)
			free_split((*g)->map_data.map);
		return (1);
	}
	return (0);
}

int	init_game(char **argv, t_data_game **g)
{
	int	i;

	i = 0;
	if (init_structs(g) != 0)
		return (1);
	if (init_map_and_flags(argv, g) != 0)
		return (1);
	if (init_mlx(g) != 0)
		return (1);
	while (i < 4)
	{
		if (init_mlx_texture(g, i) != 0)
		{
			ft_putendl_fd("Error texture file", 2);
			free_split((*g)->map_data.map);
			mlx_destroy_image((*g)->data_mlx.mlx_ptr, (*g)->data_pixel.img_ptr);
			mlx_destroy_window((*g)->data_mlx.mlx_ptr,
				(*g)->data_mlx.window_ptr);
			mlx_destroy_display((*g)->data_mlx.mlx_ptr);
			free((*g)->data_mlx.mlx_ptr);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data_game	*g;

	if (argc != 2)
		return (ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	if (check_ext(argv[1], ".cub") == -1)
		return (ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	if (init_game(argv, &g) != 0)
	{
		free_texture(g);
		free(g);
		return (1);
	}
	mlx_hook(g->data_mlx.window_ptr, KeyPress, KeyPressMask, key_code, g);
	mlx_hook(g->data_mlx.window_ptr, 17, 0, close_window, g);
	if (game_view(g) == -1)
		return (close_window(g), 1);
	mlx_loop(g->data_mlx.mlx_ptr);
	return (0);
}
