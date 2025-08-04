/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:52:10 by kkorpela          #+#    #+#             */
/*   Updated: 2025/08/04 17:25:53 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// map_loader.c

#include "so_long.h"

int	init_map(t_map *map, char *filename)
{
	int	fd;

	ft_memset(map, 0, sizeof(t_map));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (parse_error(map));
	map->rows = count_lines(fd);
	close(fd);
	if (map->rows <= 0)
		return (parse_error(map));
	map->grid = malloc(sizeof(char *) * map->rows);
	if (!map->grid)
		return (parse_error(map));
	return (1);
}

int	process_map(t_map *map, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (parse_error(map));
	if (!parse_map(map, fd))
	{
		close(fd);
		return (parse_error(map));
	}
	close(fd);
	return (1);
}
