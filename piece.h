/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:30:18 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 13:43:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIECE_H
# define PIECE_H

typedef struct	s_piece
{
	int			width;
	int			height;
	char		*data;
}				t_piece;

t_piece			*new_piece(int width, int height);
int				piece_value_at(t_piece *piece, int x, int y);

#endif
