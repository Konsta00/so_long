/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkorpela <kkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:32:52 by kkorpela          #+#    #+#             */
/*   Updated: 2025/07/24 19:54:27 by kkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft.h"
# include "mlx.h"

typedef struct	s_map
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
}				t_map;

typedef struct
{
	int		x;
	int		y;
}			t_point;


// char **parse_map(char *str);


#endif
