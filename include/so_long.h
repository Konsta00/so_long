/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:32:52 by kkorpela          #+#    #+#             */
/*   Updated: 2025/08/04 19:13:11 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <mlx.h>
# include "libft.h"

typedef struct s_point
{
	int	x;
	int	y;
}	           t_point;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		dx;
	int		dy;

}				t_enemy;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
	int		player;
	int		exit;
	int		collectibles;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		collectible_x;
	int		collectible_y;
    void    *mlx;
    void    *win;
	void	*wall_img;
	void	*floor_img;
	void	*player_img;
	void	*exit_img;
	void	*collectible_img;
	void	*exit_p_img;
	void	*move_counter_img;
	int		img_w;
	int		img_h;
	int		moves;
	t_enemy	*enemies;
	int		enemy_count;
	void	*enemy_img;
}				t_map;

/* main.c */
int		main(int ac, char **av);

/* map_loader.c / map_parser.c */
int		validate_line(char *line, t_map *map, int row);
int		parse_map(t_map *map, int fd);
int		init_map(t_map *map, char *filename);
int		process_map(t_map *map, char *filename);

/* map_utils.c */
void	free_map(t_map *map);
void	free_grid(char **map, int height);
int		parse_error(t_map *map);
int		count_lines(int fd);
void	flood_fill(char **map, int width, int height, t_point pos);
char	**duplicate_map(char **map, int height);
int		validate_player_and_exit(int player_count, int exit_count);
bool	check_reachability(char **map, int width, int height);

/* map_validate.c */
int		validate_path(t_map *map);
int		validate_walls(t_map *map);
void	set_positions(t_map *map);
void	update_position(t_map *map, char c, int i, int j);

/* game_engine.c */
void	start_game(t_map *map);
int		close_game(t_map *map);
int		handle_key(int keycode, t_map *map);
void	move_player(t_map *map, int dx, int dy);
int		win_game(t_map *map, int x, int y);
void print_map(t_map *map);


// game_enemy
void move_all_enemies(t_map *map);
void move_enemy(t_map *map, int index);
void init_enemies(t_map *map);


/* game_render.c / game_images.c */
void	init_images(t_map *map);
void	put_image(t_map *map, void *img, int x, int y);
void	render_map(t_map *map);

#endif
