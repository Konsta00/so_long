/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:56:59 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 17:57:12 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	parse_map(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	map->player = 0;
	map->exit = 0;
	map->collectibles = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!validate_line(line, map, i))
		{
			free(line);
			return (0);
		}
		map->grid[i] = line;
		i++;
		line = get_next_line(fd);
	}
	if (validate_path(map) && validate_walls(map))
		return (1);
	return (0);
}
