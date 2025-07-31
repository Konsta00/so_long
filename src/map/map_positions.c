/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_positions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:53:38 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 17:58:19 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_position(t_map *map, char c, int i, int j)
{
	if (c == 'P')
	{
		map->player_y = i;
		map->player_x = j;
	}
	else if (c == 'E')
	{
		map->exit_y = i;
		map->exit_x = j;
	}
	else if (c == 'C')
	{
		map->collectible_y = i;
		map->collectible_x = j;
	}
}

void	set_positions(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			update_position(map, map->grid[i][j], i, j);
			j++;
		}
		i++;
	}
}
