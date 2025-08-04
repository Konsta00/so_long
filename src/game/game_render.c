/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:07:52 by kkorpela          #+#    #+#             */
/*   Updated: 2025/08/04 17:44:53 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//game_render.c

#include "so_long.h"

void	render_tile(t_map *map, int x, int y, void *img)
{
	mlx_put_image_to_window(map->mlx, map->win, img, x * 64, y * 64);
}

static void	render_move_counter(t_map *map, int x, int y, void *img)
{
	char	move_str[32];

	mlx_put_image_to_window(map->mlx, map->win, img, x * 128, y * 64);
	sprintf(move_str, "%d", map->moves);
	mlx_string_put(map->mlx, map->win, x * 128 + 100, y * 64 + 40, 0xFFFFFF, move_str);
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
			else if (tile == 'G')
				render_tile(map, x, y, map->enemy_img);
			else if (map->player_x == map->exit_x
				&& map->player_y == map->exit_y
				&& map->collectibles != 0)
				render_tile(map, map->exit_x, map->exit_y, map->exit_p_img);
			x++;
		}
		y++;
	}
	render_move_counter(map, 0, 0, map->move_counter_img);

}


