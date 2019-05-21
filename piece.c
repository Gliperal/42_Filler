/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:22:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 16:33:11 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "piece.h"

static void	fill_piece(t_piece *piece, int value)
{
	int i;

	if (!piece)
		return ;
	i = 0;
	while (i < piece->width * piece->height)
	{
		piece->data[i] = value;
		i++;
	}
}

t_piece		*new_piece(int width, int height)
{
	t_piece *piece;

	if (width <= 0 || height <= 0)
		return (NULL);
	piece = (t_piece *)malloc(sizeof(t_piece));
	if (!piece)
		return (NULL);
	piece->width = width;
	piece->height = height;
	piece->data = (char *)malloc((size_t)width * height * sizeof(char));
	if (!(piece->data))
	{
		free(piece);
		return (NULL);
	}
	fill_piece(piece, 0);
	return (piece);
}
