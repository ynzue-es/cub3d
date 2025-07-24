/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/07/24 14:40:52 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data_game *data_game;
	t_flag *flag;
	
	flag = malloc(sizeof(t_flag));
	if(!flag)
		return (-1);
	data_game = malloc(sizeof(t_data_game));
	if (argc != 2)
		return (ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
	if (check_ext(argv[1]) == 0)
		return (ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
		
	ft_strlen_fd(argv[1],data_game);
	init_flag(flag);
	init_data_game(data_game);
	if(check_file(argv[1], data_game,flag) == -1)
	{
		ft_putendl_fd("Error",2);
		return (1);
	}
	if(init_map(argv[1], data_game) == -1)
	{
		ft_putendl_fd("Error",2);
		return (1);
	}

	
	// attention GNL garde \n
	//printf("%s%s", data_game->all_wall[0].texure_file, data_game->all_wall[1].texure_file);
}
// création de fenetre basique

// mlx = mlx_init();
// if (!mlx)
//     return (1);
// win = mlx_new_window(mlx, 800, 600, "Ma Fenetre MLX");
// if (!win)
//     return (1);
// mlx_loop(mlx);