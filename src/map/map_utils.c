/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:09:34 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 18:29:45 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		validate_player_and_exit(int player_count, int exit_count)
{
	if (player_count > 1 || exit_count > 1)
		return (0);
	return (1);
}

bool	check_reachability(char **map, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}


void	flood_fill(char **map, int width, int height, t_point pos)
{
	t_point	right;
	t_point	left;
	t_point	down;
	t_point	up;

	if (pos.x < 0 || pos.y < 0 || pos.x >= width || pos.y >= height)
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'V')
		return ;
	map[pos.y][pos.x] = 'V';
	right.x = pos.x + 1;
	right.y = pos.y;
	left.x = pos.x - 1;
	left.y = pos.y;
	down.x = pos.x;
	down.y = pos.y + 1;
	up.x = pos.x;
	up.y = pos.y - 1;
	flood_fill(map, width, height, right);
	flood_fill(map, width, height, left);
	flood_fill(map, width, height, down);
	flood_fill(map, width, height, up);
}

char	**duplicate_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

int		count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}
