/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:07:52 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 20:15:21 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_tile(t_map *map, int x, int y, void *img)
{
	mlx_put_image_to_window(map->mlx, map->win, img, x * 64, y * 64);
}

void	render_map(t_map *map)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			tile = map->grid[y][x];
			if (tile == '1')
				render_tile(map, x, y, map->wall_img);
			else
				render_tile(map, x, y, map->floor_img);
			if (tile == 'C')
				render_tile(map, x, y, map->collectible_img);
			else if (tile == 'E')
				render_tile(map, x, y, map->exit_img);
			else if (tile == 'P')
				render_tile(map, x, y, map->player_img);
			else if (map->player_x == map->exit_x
				&& map->player_y == map->exit_y
				&& map->collectibles != 0)
				render_tile(map, map->exit_x, map->exit_y, map->exit_p_img);

			x++;
		}
		y++;
	}
}
