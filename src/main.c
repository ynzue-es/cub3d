/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/07/25 09:47:05 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data_game *data_game;

	data_game = malloc(sizeof(t_data_game));
	if (argc != 2)
		return (ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	if (check_ext(argv[1]) == 0)
		return (ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	init_flag(&data_game->flag);
	init_data_game(data_game);
	if(check_file(argv[1], data_game,&data_game->flag) == -1)
	{
		ft_putendl_fd("Error",2);
		return (1);
	}
	if(init_map(argv[1], data_game) == -1)
	{
		ft_putendl_fd("Error",2);
		return (1);
	}

	int i = 0;
	while (data_game->map_data.map[i])
	{
		printf("line : %s\n", data_game->map_data.map[i]);
		i++;
	}
	

	free_split(data_game->map_data.map);
	free(data_game);
}
// création de fenetre basique

// mlx = mlx_init();
// if (!mlx)
//     return (1);
// win = mlx_new_window(mlx, 800, 600, "Ma Fenetre MLX");
// if (!win)
//     return (1);
// mlx_loop(mlx);