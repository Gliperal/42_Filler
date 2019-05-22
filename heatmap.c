/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:22:45 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 14:01:43 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO Remove when not printing
#include <unistd.h>

#include "map.h"

void	set_if_more(t_map *map, int x, int y, int value)
{
	if (map_value_at(map, x, y) > value)
		map_set(map, x, y, value);
}

void	pass_horizontal(t_map *map, int dir)
{
	int x;
	int y;
	int v;

	y = 0;
	while (y < map->height)
	{
		x = 2 * (0 - dir) * map->width;
		while (x != 0)
		{
			v = map_value_at(map, x, y) + 1;
			set_if_more(map, x + dir, y, v);
			x += dir;
		}
		y++;
	}
}

void	pass_vertical(t_map *map, int dir)
{
	int x;
	int y;
	int v;

	x = 0;
	while (x < map->width)
	{
		y = 2 * (0 - dir) * map->height;
		while (y != 0)
		{
			v = map_value_at(map, x, y) + 1;
			set_if_more(map, x, y + dir, v);
			y += dir;
		}
		x++;
	}
}

void		display_heatmap(t_map *map)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if(map->data[y * map->width + x] < 0)
				c = '.';
			else if (map->data[y * map->width + x] < 10)
				c = '0' + map->data[y * map->width + x];
			else
				c = 'a' - 10 + map->data[y * map->width + x];
			write(1, &c, 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}

void	heatmap(t_map *map, int enemy)
{
	int i;
	int sink;

	i = 0;
	sink = enemy ? ENEMY : HOME;
	while (i < map->width * map->height)
	{
		if (map->data[i] == sink)
			map->data[i] = 0;
		else
			map->data[i] = 0x40000000;
		i++;
	}
	pass_horizontal(map, 1);
	pass_horizontal(map, -1);
	pass_vertical(map, 1);
	pass_vertical(map, -1);
}
