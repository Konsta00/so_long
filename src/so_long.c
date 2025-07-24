/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:30:52 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/24 20:04:35 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->grid)
	{
		while (i < map->rows)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}

}

static int parse_error(t_map *map)
{
	free_map(map);
	ft_putstr_fd("Error\n", 2);
	return (0);
}



static int		count_lines(int fd)
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
			if (map->grid[i][j] == 'P')
			{
				map->player_y = i;
				map->player_x = j;
			}
			else if (map->grid[i][j] == 'E')
			{
				map->exit_y = i;
				map->exit_x = j;
			}
			else if (map->grid[i][j] == 'C')
			{
				map->collectible_y = i;
				map->collectible_x = j;
			}
			j++;
		}
		i++;
	}
}

//MAKE SURE TO GO THROUGH EACH FUNCTIONS AND REMOVE UNNECCESSERY ERROR CHECKS ETC
void	flood_fill(char **map, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, width, height);
	flood_fill(map, x - 1, y, width, height);
	flood_fill(map, x, y + 1, width, height);
	flood_fill(map, x, y - 1, width, height);
}

char	**duplicate_map(char **map, int	height)
{
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		return (NULL);
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		i++;
	}
	map_copy[height] = NULL;
	return (map_copy);
}

void	free_map_v(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
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


static int		validate_path(t_map *map)
{
	char	**map_copy;
	bool	valid;
	t_point	start = {-1, -1};

	set_positions(map);
	start.x = map->player_x;
	start.y = map->player_y;
	printf("Player pos x:%d, y:%d\n", map->player_x, map->player_y);
	printf("Exit pos x:%d, y:%d\n", map->exit_x, map->exit_y);
	printf("Collectible pos x:%d, y:%d", map->collectible_x, map->collectible_y);
	map_copy = duplicate_map(map->grid, map->rows);
	flood_fill(map_copy, start.x, start.y, map->cols, map->rows);
	valid = check_reachability(map_copy, map->cols, map->rows);
	free_map_v(map_copy, map->rows);
	return (valid);
}

static int		validate_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] != '1' || map->grid[map->rows-1][i] != '1')
			return (parse_error(map));
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->cols-1] != '1')
			return (parse_error(map));
		i++;
	}
	return (1);
}

int		validate_player_and_exit(player_count, exit_count)
{
	if (player_count > 1 || exit_count > 1)
		return (0);
	return (1);
}

int		validate_line(char *line, t_map *map, int row)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == 'P')
			map->player++;
		else if (line[i] == 'E')
			map->exit++;
		else if (line[i] == 'C')
			map->collectibles++;
		else if (line[i] != '0' && line[i] != '1')
			return (0);
		i++;
	}
	if (row == 0)
		map->cols = i;
	else if (i != map->cols)
		return (0);
	if (validate_player_and_exit(map->player, map->exit))
		return (1);
	return (0);
}

static int		parse_map(t_map *map, int fd)
{
	char	*line;
	int		i;

	map->player = 0;
	map->exit = 0;
	map->collectibles = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!validate_line(line, map, i))
		{
			free(line);
			return (0);
		}
		map->grid[i++] = line;
		printf("%s", line);
		line = get_next_line(fd);
	}
	if (validate_path(map) && validate_walls(map))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map;
	int		fd;
	int		line_count;

	if (ac != 2)
		return (parse_error(&map));
	ft_memset(&map, 0, sizeof(t_map));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (parse_error(&map));
	line_count = count_lines(fd);
	close(fd);
	if (line_count <= 0)
		return (parse_error(&map));
	map.grid = malloc(sizeof(char *) * line_count);
	if (!map.grid)
		return (parse_error(&map));
	map.rows = line_count;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		free(map.grid);
		return (parse_error(&map));
	}
	if (!parse_map(&map, fd))
	{
		parse_error(&map);
		close(fd);
		exit(1);
	}
	close(fd);
	free_map(&map);
	return (0);
}
