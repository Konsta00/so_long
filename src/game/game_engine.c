/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:20:06 by kkorpela          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:27 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #game_engine.c

#include "so_long.h"
#include <time.h>

int		game_loop(t_map *map)
{
	static clock_t last_time = 0;
	clock_t current_time = clock();
	clock_t delta_time = current_time - last_time;

	if (delta_time < 16667)
		return (0);
	last_time = current_time;
	static int enemy_move_counter = 0;
	enemy_move_counter++;
	if (enemy_move_counter >= 10)
	{
		move_all_enemies(map);
		enemy_move_counter = 0;
	}
	render_map(map);
	return (0);
}

void	start_game(t_map *map)
{
	map->moves = 0;
	srand(time(NULL));

	map->mlx = mlx_init();
	map->win = mlx_new_window(
			map->mlx,
			map->cols * 64,
			map->rows * 64,
			"so_long");
	init_images(map);
	init_enemies(map);
	render_map(map);
	mlx_key_hook(map->win, handle_key, map);
	mlx_hook(map->win, 17, 0, close_game, map);
	mlx_loop_hook(map->mlx, game_loop, map);
	mlx_loop(map->mlx);
}

int		close_game(t_map *map)
{
	free_map(map);
	mlx_destroy_window(map->mlx, map->win);
	exit(0);
	return (0);
}

int		win_game(t_map *map, int x, int y)
{
	char	tile;

	tile = map->grid[y][x];
	if (tile == 'E' && map->collectibles == 0)
	{
		map->moves += 1;
		ft_printf("Total moves: %d\n", map->moves);
		ft_printf("You win!\n");
		close_game(map);
		return (1);
	}
	return (0);
}

void print_map(t_map *map)
{
    int x;
    int y;

    ft_printf("\n=== Current Map State ===\n");
    ft_printf("Dimensions: %d columns x %d rows\n", map->cols, map->rows);
    ft_printf("Legend: 1=Wall, 0=Empty, P=Player, C=Collectible, E=Exit, G=Enemy\n");
    ft_printf("Map borders:\n");

    // Print top border with coordinates
    ft_printf("    ");
    for (x = 0; x < map->cols; x++) {
        ft_printf("%-2d", x % 10);  // Print x coordinate (0-9 repeating)
    }
    ft_printf("\n    ");
    for (x = 0; x < map->cols; x++) {
        ft_printf("--");
    }
    ft_printf("\n");

    // Print each row with y coordinate
    y = 0;
    while (y < map->rows)
    {
        ft_printf("%2d |", y);  // Print y coordinate

        x = 0;
        while (x < map->cols)
        {
            // Print the map character with spacing
            ft_printf(" %c", map->grid[y][x]);
            x++;
        }
        ft_printf("\n");
        y++;
    }

    // Print bottom border
    ft_printf("    ");
    for (x = 0; x < map->cols; x++) {
        ft_printf("--");
    }
    ft_printf("\n");

    // Print player and enemy positions
    ft_printf("Player position: (%d,%d)\n", map->player_x, map->player_y);
    ft_printf("Exit position: (%d,%d)\n", map->exit_x, map->exit_y);
    ft_printf("Collectibles remaining: %d\n", map->collectibles);

    // Print all enemy positions
    if (map->enemy_count > 0) {
        ft_printf("Enemies (%d):\n", map->enemy_count);
        for (int i = 0; i < map->enemy_count; i++) {
            ft_printf("  Enemy %d at (%d,%d) moving (%d,%d)\n",
                     i,
                     map->enemies[i].x,
                     map->enemies[i].y,
                     map->enemies[i].dx,
                     map->enemies[i].dy);
        }
    }
    ft_printf("========================\n\n");
}
