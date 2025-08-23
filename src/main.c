/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:52:58 by yannis            #+#    #+#             */
/*   Updated: 2025/08/23 14:38:09 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int init_mlx(t_window **data_mlx, t_data_pixel **data_pixel)
{
    (*data_mlx)->mlx_ptr = mlx_init();
    if (!(*data_mlx)->mlx_ptr)
        return (1);
    (*data_mlx)->window_ptr = mlx_new_window((*data_mlx)->mlx_ptr, 2000, 1090, "cub3d");
    if (!(*data_mlx)->window_ptr)
        return (1);
    (*data_pixel)->img_ptr = mlx_new_image((*data_mlx)->mlx_ptr, 2000, 1090);
    (*data_pixel)->addr = mlx_get_data_addr((*data_pixel)->img_ptr, &(*data_pixel)->bits_per_pixel,
                             &(*data_pixel)->line_length, &(*data_pixel)->endian);
    return (0);
}

static int init_structs(t_data_game **data_game, t_window **data_mlx, t_data_pixel **data_pixel)
{
    *data_pixel = malloc(sizeof(t_data_pixel));
    *data_game = malloc(sizeof(t_data_game));
    *data_mlx = malloc(sizeof(t_window));
    if (!*data_pixel || !*data_game || !*data_mlx)
        return (1);
    return (0);
}

static int init_map_and_flags(int argc, char **argv, t_data_game **data_game)
{
    if (argc != 2)
        return (free(*data_game), ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
    if (check_ext(argv[1], ".cub") == -1)
        return (free(*data_game), ft_putendl_fd("Usage : ./cub3d filename.cub", 2), 1);
    init_flag(&(*data_game)->flag);
    init_data_game(*data_game);
    if (check_file(argv[1], *data_game, &(*data_game)->flag) == -1)
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

int init_game(int argc, char **argv, t_data_game **data_game, t_window **data_mlx, t_data_pixel **data_pixel)
{
    if (init_structs(data_game, data_mlx, data_pixel) != 0)
        return (1);
    if (init_map_and_flags(argc, argv, data_game) != 0)
        return (1);
    if (init_mlx(data_mlx, data_pixel) != 0)
        return (1);
    (*data_game)->data_mlx = *data_mlx;
    (*data_game)->data_pixel = *data_pixel;
    return (0);
}

int main(int argc, char **argv)
{
	t_data_game *data_game;
	t_window *data_mlx;
	t_data_pixel *data_pixel;

	if (init_game(argc, argv, &data_game, &data_mlx, &data_pixel) != 0)
		return (1);
	mlx_hook(data_mlx->window_ptr, KeyPress, KeyPressMask, key_code, data_game);
	game_view(data_mlx, data_game, data_pixel);
	mlx_loop(data_mlx->mlx_ptr);
	free_split(data_game->map_data.map);
	free(data_game);
	return (0);
}
