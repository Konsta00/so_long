/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:51:22 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 20:15:33 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_images(t_map *map)
{
	map->wall_img = mlx_xpm_file_to_image(
			map->mlx,
			"resources/images/wall_64.xpm",
			&map->img_w,
			&map->img_h);
	map->floor_img = mlx_xpm_file_to_image(
			map->mlx,
			"resources/images/floor_64.xpm",
			&map->img_w,
			&map->img_h);
	map->player_img = mlx_xpm_file_to_image(
			map->mlx,
			"resources/images/player_floor_64.xpm",
			&map->img_w,
			&map->img_h);
	map->exit_img = mlx_xpm_file_to_image(
			map->mlx,
			"resources/images/exit_floor_64.xpm",
			&map->img_w,
			&map->img_h);
	map->collectible_img = mlx_xpm_file_to_image(
			map->mlx,
			"resources/images/collectible_floor_64.xpm",
			&map->img_w,
			&map->img_h);
	map->exit_p_img = mlx_xpm_file_to_image(
			map->mlx,
			"resources/images/exit_player_floor_64.xpm",
			&map->img_w,
			&map->img_h);
}
