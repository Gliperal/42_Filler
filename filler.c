/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:09:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 14:28:17 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

// TODO Remove (replace with stdin)
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	char *line;

	int fd = open("resources/sample_input2", O_RDONLY);
	t_map *map = input_map(fd, &line);
	if (!map)
		return (-1);
	t_piece *piece = input_piece(fd, line);
	free(line);
	if (!piece)
		return (-1);
	printf("end\n");
	printf("Player #%d\n", map->player);
	printf("map %dx%d\n", map->width, map->height);
	map_display(map);
	printf("Piece %dx%x\n", piece->width, piece->height);
	for(int y = 0; y < piece->height; y++)
	{
		for (int x = 0; x < piece->width; x++)
		{
			if (piece->data[y * piece->width + x])
				write(1, "#", 1);
			else
				write(1, "_", 1);
		}
		write(1, "\n", 1);
	}
	int best_move[2];
	map_calculate(map, piece, best_move);
	printf("Best move: %d, %d\n", best_move[0], best_move[1]);
	/*
	int (*legal_moves)[2];
	game_legal_moves(map, piece, &legal_moves);
	t_map *map2 = new_map(map->width, map->height);
	int i = 0;
	while (legal_moves[i][0] != 2147483647)
	{
		map_cpy(map2, map);
		game_move(map2, piece, legal_moves[i]);
		printf("Move %d, %d\n", legal_moves[i][0], legal_moves[i][1]);
		display_map(map2);
		i++;
	}
	*/
	while (1) {}
}
