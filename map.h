/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 21:37:24 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 21:08:26 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define EMPTY 0
# define HOME 2147483647
# define ENEMY -2147483648

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
int				map_value_at(t_map *map, int x, int y);
void			map_cpy(t_map *dst, t_map *src);

#endif
