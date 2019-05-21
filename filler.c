/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:09:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/21 15:43:07 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "map.h"
#include "piece.h"

// TODO Remove (replace with stdin)
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	read_player(int fd)
{
	char *line;
	int player;
	int status;

	status = get_next_line(fd, &line);
	if (status != 1)
		return (0);
	if (!ft_strnequ(line, "$$$ exec p", 10))
		return (0);
	player = line[10] - '0';
	if (player < 1 || player > 2)
		return (0);
	free(line);
	return (player);
}

static t_map	*read_map_header(int fd)
{
	char *line;
	t_map *map;
	int width;
	int height;
	int status;

	status = get_next_line(fd, &line);
	if (status != 1)
		return (NULL);
	if (!ft_strnequ(line, "Plateau", 7))
		return (NULL);
	height = ft_pop_atoi(line + 7);
	width = ft_pop_atoi(line + 7);
	map = new_map(width, height);
	free(line);
	return (map);
}

static void	read_map_row(t_map *map, char *line)
{
	int row;
	int i;

	if (!ft_isdigit(*line))
		return ;
	row = ft_pop_atoi(line);
	if (row < 0 || row >= map->height)
		return ;
	char *data = ft_strtrim(line);
	i = 0;
	while (data[i] && i < map->width)
	{
		if (data[i] == '.')
			map_set(map, i, row, ',');
		else if (data[i] == 'o' || data[i] == 'O')
			map_set(map, i, row, '0');
		else if (data[i] == 'x' || data[i] == 'X')
			map_set(map, i, row, 'k');
		i++;
	}
	free(data);
}

static t_piece	*read_piece_header(char *line)
{
	t_piece *piece;
	int width;
	int height;

	if (!piece)
		return (NULL);
	if (!ft_strnequ(line, "Piece", 5))
		return (NULL);
	height = ft_pop_atoi(line + 5);
	width = ft_pop_atoi(line + 5);
	piece = new_piece(width, height);
	return (piece);
}

static void	read_piece_row(t_piece *piece, char *line, int row)
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

int	main()
{
	char *line;
	int player;

	int fd = open("resources/sample_input", O_RDONLY);
	player = -1;
	t_map *map = NULL;
	player = read_player(fd);
	map = read_map_header(fd);
	if (!player || !map)
		return (-1);
	printf("Player #%d\n", player);
	printf("map %dx%d\n", map->width, map->height);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strnequ(line, "Piece", 5))
			break ;
		else
			read_map_row(map, line);
		free(line);
	}
	display_map(map);
	t_piece *piece;
	piece = read_piece_header(line);
	free(line);
	if (!piece)
		return (-1);
	printf("Piece %dx%x\n", piece->width, piece->height);
	int row = 0;
	while (get_next_line(fd, &line) == 1)
	{
		read_piece_row(piece, line, row);
		row++;
		free(line);
	}
	printf("end\n");
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
	while (1) {}
}
