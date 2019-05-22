/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap_evaluate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:03:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 21:23:29 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	heatmap(t_map *map, int enemy);
void		display_heatmap(t_map *map);

int	heatmap_evaluate(t_map *map)
{
	t_map *map2 = new_map(map->width, map->height);

	// TODO Store the enemy heatmap somewhere static and pass it in
	map_cpy(map2, map);
	heatmap(map, 0);
	display_heatmap(map);
	heatmap(map2, 1);
	display_heatmap(map2);
	int eval = 0;
	int i = 0;
	while (i < map->width * map->height)
	{
		if (map->data[i] && map2->data[i])
			if (map->data[i] > map2->data[i])
				eval++;
		i++;
	}
	return (eval);
}
