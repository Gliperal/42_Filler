/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:19:08 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 14:24:06 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdlib.h>
# include <unistd.h>

# include "map.h"
# include "piece.h"
# include "libft/libft.h"

# define BASE_MAP 0
# define HOME_MAP 1
# define ENEMY_MAP 2

t_map	*input_map(int fd, char **line);
t_piece	*input_piece(int fd, char *header);
int		map_calculate(t_map *map, t_piece *piece, int best_move[2]);
void	game_legal_moves(t_map *map, t_piece *piece, int (**legal_moves)[2]);
void	game_move(t_map *map, t_piece *piece, int move[2]);
void	heatmap(t_map *map, int enemy);
void	display_heatmap(t_map *map);

#endif
