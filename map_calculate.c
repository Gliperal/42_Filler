/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:19:46 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 14:08:04 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"
#include "piece.h"

void	game_legal_moves(t_map *map, t_piece *piece, int (**legal_moves)[2]);
void	game_move(t_map *map, t_piece *piece, int move[2]);
void	heatmap(t_map *map, int enemy);

// TODO Move to header file
#define BASE_MAP 0
#define HOME_MAP 1
#define ENEMY_MAP 2

static int	evaluate_move(t_map *maps[3], t_piece *piece, int move[2])
{
	int eval;
	int i;

	game_move(maps[HOME_MAP], piece, move);
	heatmap(maps[HOME_MAP], 0);
	eval = 0;
	i = 0;
	while (i < maps[HOME_MAP]->width * maps[HOME_MAP]->height)
	{
		if (maps[HOME_MAP]->data[i] && maps[ENEMY_MAP]->data[i])
			if (maps[HOME_MAP]->data[i] < maps[ENEMY_MAP]->data[i])
				eval++;
		i++;
	}
	return (eval);
}

static void	mc(t_map *maps[3], t_piece *piece, int b_move[2], int (*moves)[2])
{
	int eval;
	int best_eval;
	int i;

	best_eval = -2147483648;
	i = 0;
	while (moves[i][0] != 2147483647)
	{
		map_cpy(maps[HOME_MAP], maps[BASE_MAP]);
		eval = evaluate_move(maps, piece, moves[i]);
		if (eval > best_eval)
		{
			b_move[0] = moves[i][0];
			b_move[1] = moves[i][1];
			best_eval = eval;
		}
		i++;
	}
}

/*
** Calculates all the possible moves for map and assigns the best one to the
** argument best_move. Returns 0 on success or greater than 0 on failure.
*/

int			map_calculate(t_map *map, t_piece *piece, int best_move[2])
{
	t_map	*maps[3];
	int		(*legal_moves)[2];

	maps[BASE_MAP] = map;
	maps[HOME_MAP] = new_map(map->width, map->height);
	if (!maps[HOME_MAP])
		return (1);
	maps[ENEMY_MAP] = new_map(map->width, map->height);
	if (!maps[ENEMY_MAP])
		return (1);
	game_legal_moves(map, piece, &legal_moves);
	if (!legal_moves)
		return (1);
	map_cpy(maps[ENEMY_MAP], map);
	heatmap(maps[ENEMY_MAP], 1);
	mc(maps, piece, best_move, legal_moves);
	free(legal_moves);
	free(maps[HOME_MAP]);
	free(maps[ENEMY_MAP]);
	return (0);
}
