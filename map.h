/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 21:37:24 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 14:24:55 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct	s_map
{
	int			player;
	int			width;
	int			height;
	int			*data;
}				t_map;

t_map			*new_map(int width, int height);
int				map_set(t_map *map, int x, int y, int value);
void			display_map(t_map *map);

#endif
