/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:23:53 by kkorpela          #+#    #+#             */
/*   Updated: 2025/08/04 19:25:53 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"

void init_enemies(t_map *map)
{
	ft_printf("init_enemies()\n");
	int count;
	int i;
	int	x;
	int	y;

	count = 0;
	x = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->grid[y][x] == 'G')
			{
				ft_printf("Found G at x:%d, y:%d", x, y);
				count++;
			}
			x++;
		}
		y++;
	}

	map->enemy_count = count;
	ft_printf("amount of enemies=%i\n", map->enemy_count);

	if (count == 0)
		return ;

	map->enemies = malloc(sizeof(t_enemy) * count);
	if (!map->enemies)
		return;

	i = 0;
	y = 0;
	x = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->grid[y][x] == 'G')
			{
				map->enemies[i].x = x;
				map->enemies[i].y = y;
				map->enemies[i].dx = 0;
				map->enemies[i].dy = 0;
				if (x < map->cols - 1 && map->grid[y][x+1] != '1')
					map->enemies[i].dx = 1;
				i++;
			}
			x++;
		}
		y++;
	}
}

void move_enemy(t_map *map, int index)
{
	t_enemy *enemy;
	int new_x;
	int new_y;

	enemy = &map->enemies[index];
	new_x = enemy->x + 1;
	new_y = enemy->y;

	if (new_x <= 0 || new_x >= map->cols - 1 ||
		new_y <= 0 || new_y >= map->rows - 1 ||
		map->grid[new_y][new_x] == '1')
	{
		int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
		int attempts = 0;

		while (attempts < 4)
		{
			int dir = rand() % 4;
			enemy->dx = directions[dir][0];
			enemy->dy = directions[dir][1];

			new_x = enemy->x + enemy->dx;
			new_y = enemy->y + enemy->dy;
			if (new_x > 0 && new_x < map->cols - 1 &&
				new_y > 0 && new_y < map->rows - 1 &&
				map->grid[new_y][new_x] != '1')
			{
				break;
			}
			attempts++;
		}

		if (attempts >= 4)
		{
			enemy->dx = 0;
			enemy->dy = 0;
			return ;
		}
	}
	if (map->grid[enemy->y][enemy->x] == 'G')
		map->grid[enemy->y][enemy->x] = '0';

	enemy->x = new_x;
	enemy->y = new_y;
	map->grid[new_y][new_x] = 'G';
	if (enemy->x == map->player_x && enemy->y == map->player_y)
	{
		ft_printf("Game Over! You were caught by an enemy!\n");
		close_game(map);
	}
}

void 	move_all_enemies(t_map *map)
{
	int	i;

	i = 0;
	print_map(map);
	ft_printf("Moving %d enemies\n", map->enemy_count);
	while (i < map->enemy_count)
	{
		if (map->enemies[i].x >= 0 && map->enemies[i].x < map->cols &&
			map->enemies[i].y >= 0 && map->enemies[i].y < map->rows)
			{
				move_enemy(map, i);
			}
		i++;
	}
}
