/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:09:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 16:44:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft/libft.h"
#include "piece.h"

static t_piece	*read_piece_header(char *line)
{
	t_piece	*piece;
	int		width;
	int		height;

	if (!ft_strnequ(line, "Piece", 5))
		return (NULL);
	height = ft_pop_atoi(line + 5);
	width = ft_pop_atoi(line + 5);
	piece = new_piece(width, height);
	return (piece);
}

static void		read_piece_row(t_piece *piece, char *line, int row)
{
	int i;

	if (row < 0 || row >= piece->height)
		return ;
	i = 0;
	while (line[i] && i < piece->width)
	{
		if (line[i] == '.')
			piece->data[row * piece->width + i] = 0;
		else if (line[i] == '*')
			piece->data[row * piece->width + i] = 1;
		i++;
	}
}

t_piece			*input_piece(int fd, char *header)
{
	t_piece	*piece;
	char	*line;
	int		row;

	piece = read_piece_header(header);
	if (!piece)
		return (NULL);
	row = 0;
	while (get_next_line(fd, &line) == 1)
	{
		read_piece_row(piece, line, row);
		row++;
		free(line);
	}
	return (piece);
}
