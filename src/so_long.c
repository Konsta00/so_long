/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:30:52 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/31 20:51:08 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (0);
	if (!init_map(&map, av[1]))
		return (1);
	if (!process_map(&map, av[1]))
		return (1);
	start_game(&map);
	free_map(&map);
	return (0);
}
