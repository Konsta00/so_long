/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:12:05 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 20:09:18 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, t_map *map)
{
	if (keycode == 65307)
		close_game(map);
	else if (keycode == 'W' || keycode == 'w' || keycode == 65362)
		move_player(map, 0, -1);
	else if (keycode == 'S' || keycode == 's' || keycode == 65364)
		move_player(map, 0, 1);
	else if (keycode == 'A' || keycode == 'a' || keycode == 65361)
		move_player(map, -1, 0);
	else if (keycode == 'D' || keycode == 'd' || keycode == 65363)
		move_player(map, 1, 0);
	return (0);
}

void	move_player(t_map *map, int dx, int dy)
{
	static int	moves;
	int			x;
	int			y;
	char		tile;

	x = map->player_x + dx;
	y = map->player_y + dy;
	tile = map->grid[y][x];
	if (tile == '1')
		return ;
	if (tile == 'C')
		map->collectibles--;
	if (win_game(map, x, y, &moves))
		return ;
	if (map->grid[map->player_y][map->player_x] != 'E')
		map->grid[map->player_y][map->player_x] = '0';
	if (map->grid[y][x] != 'E')
		map->grid[y][x] = 'P';
	map->player_x = x;
	map->player_y = y;
	moves += 1;
	ft_printf("Moves: %d\n", moves);
	render_map(map);
}
