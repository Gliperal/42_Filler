/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:35:32 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 13:29:38 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"
#include "piece.h"

static int	legal_move(t_map *map, t_piece *piece, int x, int y)
{
	int connected;
	int i;
	int j;

	connected = 0;
	j = 0;
	while (j < piece->height)
	{
		i = 0;
		while (i < piece->width)
		{
			if (piece->data[j * piece->width + i] && map_value_at(map, x + i, y + j) == HOME)
			{
				if (connected)
					return (0);
				else
					connected = 1;
			}
			i++;
		}
		j++;
	}
	return (connected);
}

static int	count_legal_moves(t_map *map, t_piece *piece)
{
	int x;
	int y;
	int i;

	y = 0 - map->width;
	i = 0;
	while (y < 0)
	{
		x = 0 - map->width;
		while (x < 0)
		{
			if (legal_move(map, piece, x, y))
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

void	game_move(t_map *map, t_piece *piece, int move[2])
{
	int x;
	int y;

	y = 0;
	while (y < piece->height)
	{
		x = 0;
		while (x < piece->width)
		{
			if (piece->data[y * piece->width + x])
				map_set(map, move[0] + x, move[1] + y, HOME);
			x++;
		}
		y++;
	}
}

void	game_legal_moves(t_map *map, t_piece *piece, int (**legal_moves)[2])
{
	int x;
	int y;
	int i;

	i = count_legal_moves(map, piece);
	if (i == 0)
	{
		*legal_moves = NULL;
		return ;
	}
	*legal_moves = malloc(sizeof(int[i + 1][2]));
	if (!(*legal_moves))
		return ;
	y = 0 - map->width;
	i = 0;
	while (y < 0)
	{
		x = 0 - map->width;
		while (x < 0)
		{
			if (legal_move(map, piece, x, y))
			{
				(*legal_moves)[i][0] = x;
				(*legal_moves)[i][1] = y;
				i++;
			}
			x++;
		}
		y++;
	}
	(*legal_moves)[i][0] = 2147483647;
}
