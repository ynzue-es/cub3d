/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/09/04 14:13:41 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx(t_data_game **g)
{
	(*g)->data_mlx.mlx_ptr = mlx_init();
	if (!(*g)->data_mlx.mlx_ptr)
		return (1);
	(*g)->data_mlx.window_ptr = mlx_new_window((*g)->data_mlx.mlx_ptr,
			(*g)->data_mlx.width, (*g)->data_mlx.height, "cub3d");
	if (!(*g)->data_mlx.window_ptr)
		return (1);
	(*g)->data_pixel.img_ptr = mlx_new_image((*g)->data_mlx.mlx_ptr,
			(*g)->data_mlx.width, (*g)->data_mlx.height);
	if (!(*g)->data_pixel.img_ptr)
		return (1);
	(*g)->data_pixel.addr = mlx_get_data_addr((*g)->data_pixel.img_ptr,
			&(*g)->data_pixel.bits_per_pixel, &(*g)->data_pixel.line_length,
			&(*g)->data_pixel.endian);
	if (!(*g)->data_pixel.addr)
		return (1);
	return (0);
}

int	init_mlx_texture(t_data_game **g, int i)
{
	(*g)->wall_t[i].img_ptr = mlx_xpm_file_to_image((*g)->data_mlx.mlx_ptr,
			(*g)->all_wall[i].texure_file, &(*g)->wall_t[i].width,
			&(*g)->wall_t[i].height);
	if (!(*g)->wall_t[i].img_ptr)
		return (1);
	(*g)->wall_t[i].addr = mlx_get_data_addr((*g)->wall_t[i].img_ptr,
			&(*g)->wall_t[i].bits_per_pixel, &(*g)->wall_t[i].line_length,
			&(*g)->wall_t[i].endian);
	if (!(*g)->wall_t[i].addr)
		return (1);
	return (0);
}

static int	init_structs(t_data_game **g)
{
	*g = malloc(sizeof(t_data_game));
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
		ft_putendl_fd("Error", 2);
		free(*g);
		return (1);
	}
	if (init_map(argv[1], *g) == -1)
	{
		ft_putendl_fd("Error", 2);
		free(*g);
		return (1);
	}
	return (0);
}

int	init_data_gameame(int argc, char **argv, t_data_game **g)
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

	if (init_data_gameame(argc, argv, &g) != 0)
		return (1);
	mlx_hook(g->data_mlx.window_ptr, KeyPress, KeyPressMask, key_code, g);
	game_view(g);
	mlx_loop(g->data_mlx.mlx_ptr);
	free_split(g->map_data.map);
	free(g);
	return (0);
}
