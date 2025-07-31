/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:53:38 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 18:27:20 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



static int	validate_chars(char *line, int row, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'P')
			map->player++;
		else if (line[i] == 'E')
			map->exit++;
		else if (line[i] == 'C')
			map->collectibles++;
		else if (line[i] != '0' && line[i] != '1')
		{
			ft_printf("Invalid character '%c' at row %d, col %d\n",
				line[i], row, i);
			return (0);
		}
		i++;
	}
	return (i);
}

int	validate_line(char *line, t_map *map, int row)
{
	int	len;

	len = validate_chars(line, row, map);
	if (len == 0)
		return (0);
	if (row == 0)
		map->cols = len;
	else if (len != map->cols)
		return (0);
	return (validate_player_and_exit(map->player, map->exit));
}

int	validate_path(t_map *map)
{
	t_point	start;
	char	**map_copy;
	bool	valid;

	set_positions(map);
	start.x = map->player_x;
	start.y = map->player_y;
	map_copy = duplicate_map(map->grid, map->rows);
	flood_fill(map_copy, map->cols, map->rows, start);
	valid = check_reachability(map_copy, map->cols, map->rows);
	free_grid(map_copy, map->rows);
	return (valid);
}

int	validate_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] != '1')
			return (parse_error(map));
		if (map->grid[map->rows - 1][i] != '1')
			return (parse_error(map));
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] != '1')
			return (parse_error(map));
		if (map->grid[i][map->cols - 1] != '1')
			return (parse_error(map));
		i++;
	}
	return (1);
}
