/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:22:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 14:27:17 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "map.h"

void		map_display(t_map *map)
{
	int		x;
	int		y;

	if (!map)
	{
		write(1, "(null)\n", 7);
		return ;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->data[y * map->width + x] == HOME)
				write(1, "@", 1);
			else if (map->data[y * map->width + x] == ENEMY)
				write(1, "#", 1);
			else
				write(1, ".", 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
