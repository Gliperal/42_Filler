/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:22:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 21:16:47 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "map.h"

static void	fill_map(t_map *map, int value)
{
	int i;

	if (!map)
		return ;
	i = 0;
	while (i < map->width * map->height)
	{
		map->data[i] = value;
		i++;
	}
}

t_map		*new_map(int width, int height)
{
	t_map *map;

	if (width <= 0 || height <= 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->data = (int *)malloc((size_t)width * height * sizeof(int));
	if (!(map->data))
	{
		free(map);
		return (NULL);
	}
	fill_map(map, EMPTY);
	return (map);
}

int			map_value_at(t_map *map, int x, int y)
{
	if (!map || !(map->data))
		return (0);
	while (x < 0)
		x += map->width;
	x %= map->width;
	while (y < 0)
		y += map->height;
	y %= map->height;
	return (map->data[y * map->width + x]);
}

int			map_set(t_map *map, int x, int y, int value)
{
	if (!map || !(map->data))
		return (0);
	while (x < 0)
		x += map->width;
	x %= map->width;
	while (y < 0)
		y += map->height;
	y %= map->height;
	map->data[y * map->width + x] = value;
	return (1);
}

void		map_cpy(t_map *dst, t_map *src)
{
	if (!dst || !src)
		return ;
	if (dst->width != src->width)
		return ;
	if (dst->height != src->height)
		return ;
	ft_memcpy(dst->data, src->data, src->width * src->height * sizeof(int));
}

void		display_map(t_map *map)
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
			if(map->data[y * map->width + x] == HOME)
				write(1, "@", 1);
			else if(map->data[y * map->width + x] == ENEMY)
				write(1, "#", 1);
			else
				write(1, ".", 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
