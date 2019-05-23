/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:35:32 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 18:16:03 by nwhitlow         ###   ########.fr       */
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
	int value;

	connected = 0;
	j = 0;
	while (j < piece->height)
	{
		i = 0;
		while (i < piece->width)
		{
			value = map_value_at(map, x + i, y + j);
			if (value == ENEMY)
				return (0);
			if (piece_value_at(piece, i, j) && value == HOME)
				connected++;
			if (connected == 2)
				return (0);
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

	y = 0 - map->height;
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

static void	fill_legal_moves(t_map *map, t_piece *piece, int (**moves)[2])
{
	int x;
	int y;
	int i;

	y = 0 - map->height;
	i = 0;
	while (y < 0)
	{
		x = 0 - map->width;
		while (x < 0)
		{
			if (legal_move(map, piece, x, y))
			{
				(*moves)[i][0] = x;
				(*moves)[i][1] = y;
				i++;
			}
			x++;
		}
		y++;
	}
	(*moves)[i][0] = 2147483647;
}

void		game_legal_moves(t_map *map, t_piece *piece, int (**moves)[2])
{
	int size;

	size = count_legal_moves(map, piece);
	if (size == 0)
	{
		*moves = NULL;
		return ;
	}
	*moves = malloc(sizeof(int[size + 1][2]));
	if (!(*moves))
		return ;
	fill_legal_moves(map, piece, moves);
}

void		game_move(t_map *map, t_piece *piece, int move[2])
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
