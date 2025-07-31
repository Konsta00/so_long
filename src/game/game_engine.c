/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:20:06 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 19:46:24 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_game(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(
			map->mlx,
			map->cols * 64,
			map->rows * 64,
			"so_long");
	init_images(map);
	render_map(map);
	mlx_key_hook(map->win, handle_key, map);
	mlx_hook(map->win, 17, 0, close_game, map);
	mlx_loop(map->mlx);
}

int		close_game(t_map *map)
{
	free_map(map);
	mlx_destroy_window(map->mlx, map->win);
	exit(0);
	return (0);
}

int		win_game(t_map *map, int x, int y, int *moves)
{
	char	tile;

	tile = map->grid[y][x];
	if (tile == 'E' && map->collectibles == 0)
	{
		*moves = *moves + 1;
		ft_printf("Total moves: %d\n", *moves);
		ft_printf("You win!\n");
		close_game(map);
		return (1);
	}
	return (0);
}
