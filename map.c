/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:22:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 14:25:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"
#include "libft/libft.h"

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
