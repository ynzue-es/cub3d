/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/08/05 12:02:07 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data_game	*data_game;
	void *mlx_ptr;
	void *window;
	
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
    	return (1);
	window = mlx_new_window(mlx_ptr, 3840, 2090, "cub3d");
	if (!window)
    	return (1);
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
	mlx_loop(mlx_ptr);
	free_split(data_game->map_data.map);
	free(data_game);
}





