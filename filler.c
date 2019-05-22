/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:09:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 14:50:43 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	main(void)
{
	t_map	*map;
	t_piece	*piece;
	char	*line;
	int		best_move[2];

	map = input_map(0, &line);
	if (!map)
		return (-1);
	piece = input_piece(0, line);
	free(line);
	if (!piece)
		return (-1);
	map_calculate(map, piece, best_move);
	ft_putnbr(best_move[1]);
	write(1, " ", 1);
	ft_putnbr(best_move[0]);
	write(1, "\n", 1);
	free(map->data);
	free(map);
	free(piece->data);
	free(piece);
	return (0);
}
