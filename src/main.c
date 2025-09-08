/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/09/08 13:12:04 by engiusep         ###   ########.fr       */
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

static int	init_map_and_flags(int argc, char **argv, t_data_game **g)
{
	if (argc != 2)
		return (free(*g), ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	if (check_ext(argv[1], ".cub") == -1)
		return (free(*g), ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	init_flag(&(*g)->flag);
	init_data_game(*g);
	if (check_file(argv[1], g) == -1)
	{
		ft_putendl_fd("Error file in parsing", 2);
		free_texture(*g);
		free(*g);
		return (1);
	}
	if (init_map(argv[1], *g) == -1)
	{
		ft_putendl_fd("Error file map", 2);
		free_texture(*g);
		free(*g);
		return (1);
	}
	return (0);
}

int	init_game(int argc, char **argv, t_data_game **g)
{
	int	i;

	i = 0;
	if (init_structs(g) != 0)
		return (1);
	if (init_map_and_flags(argc, argv, g) != 0)
		return (1);
	if (init_mlx(g) != 0)
		return (1);
	while (i < 4)
	{
		if (init_mlx_texture(g, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data_game	*g;

	if (init_game(argc, argv, &g) != 0)
	{
		return (1);
	}
	mlx_hook(g->data_mlx.window_ptr, KeyPress, KeyPressMask, key_code, g);
	game_view(g);
	mlx_loop(g->data_mlx.mlx_ptr);
	return (0);
}
