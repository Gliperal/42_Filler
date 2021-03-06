/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:09:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 17:50:42 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft/libft.h"
#include "map.h"

static t_map	*read_map_header(int fd)
{
	char	*line;
	t_map	*map;
	int		width;
	int		height;
	int		status;

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

static void		read_map_row(t_map *map, char *line)
{
	int		row;
	int		i;
	char	*data;
	int		value;

	if (!ft_isdigit(*line))
		return ;
	row = ft_pop_atoi(line);
	if (row < 0 || row >= map->height)
		return ;
	data = ft_strtrim(line);
	i = 0;
	while (data[i] && i < map->width)
	{
		value = EMPTY;
		if (data[i] == 'o' || data[i] == 'O')
			value = (map->player == 1) ? HOME : ENEMY;
		else if (data[i] == 'x' || data[i] == 'X')
			value = (map->player == 1) ? ENEMY : HOME;
		map_set(map, i, row, value);
		i++;
	}
	free(data);
}

t_map			*input_map(int fd, char **line, int player)
{
	t_map	*map;

	map = read_map_header(fd);
	if (!map)
		return (NULL);
	map->player = player;
	while (get_next_line(fd, line) == 1)
	{
		if (ft_strnequ(*line, "Piece", 5))
			break ;
		else
			read_map_row(map, *line);
		free(*line);
	}
	return (map);
}
