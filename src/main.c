/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/08/06 11:16:59 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data_game	*data_game;
	t_window data_mlx;
	
	
	data_game = malloc(sizeof(t_data_game));
	if (argc != 2)
		return (free(data_game), ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	if (check_ext(argv[1], ".cub") == -1)
		return (free(data_game), ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	init_flag(&data_game->flag);
	init_data_game(data_game);
	if (check_file(argv[1], data_game, &data_game->flag) == -1)
	{
		ft_putendl_fd("Error", 2);
		free(data_game);
		return (1);
	}
	if (init_map(argv[1], data_game) == -1)
	{
		ft_putendl_fd("Error", 2);
		free(data_game);
		return (1);
	}
	data_mlx.mlx_ptr = mlx_init();
	if (!data_mlx.mlx_ptr)
    	return (1);
	data_mlx.window_ptr = mlx_new_window(data_mlx.mlx_ptr, 2000, 1090, "cub3d");
	if (!data_mlx.window_ptr)
    	return (1);
	put_segment(&data_mlx,data_game);
	mlx_loop(data_mlx.mlx_ptr);
	free_split(data_game->map_data.map);
	free(data_game);
}





