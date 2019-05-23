/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 12:09:43 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/22 17:51:22 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft/libft.h"

int	input_player(int fd)
{
	char	*line;
	int		player;
	int		status;

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
