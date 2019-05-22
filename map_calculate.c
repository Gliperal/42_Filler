/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:19:46 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 13:25:13 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	evaluate_move(t_map *map, int move[2], t_map *enemy_heatmap)
{
	int eval;
	int i;

	game_move(map, move);
	heatmap(map, 0);
	eval = 0;
	i = 0;
	while (i < map->width * map->height)
	{
		if (home_heatmap->data[i] && enemy_heatmap->data[i])
			if (home_heatmap->data[i] < enemy_heatmap->data[i])
				eval++;
		i++;
	}
	return (eval);
}

/*
** Calculates all the possible moves for map and assigns the best one to the argument
** best_move. Returns 0 on success or greater than 0 on failure.
*/

#define 0 BASE_MAP
#define 1 HOME_MAP
#define 2 ENEMY_MAP

static int mc(t_map maps[3], t_piece *piece, int best_move[2], int (*moves)[2])
{
	int eval;
	int best_eval;

	best_eval = -2147483648;
	while (moves[0][0] != 2147483647)
	{
		map_cpy(maps[HOME_MAP], maps[BASE_MAP]);
		eval = evaluate_move(maps[HOME_MAP], moves[i], maps[ENEMY_MAP]);
		if (eval > best_eval)
		{
			best_move[0] = moves[0][0];
			best_move[1] = moves[0][1];
			best_eval = eval;
		}
		moves += 2;
	}
}

int	map_calculate(t_map *map, t_piece *piece, int best_move[2])
{
	t_map maps[3];
	int (*legal_moves)[2];

	maps[BASE_MAP] = map;
	maps[HOME_MAP] = new_map(map->width, map->height);
	if (!maps[HOME_MAP])
		return (1);
	maps[ENEMY_MAP] = new_map(map->width, map->height);
	if (!maps[ENEMY_MAP])
		return (1);
	game_legal_moves(&legal_moves);
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
