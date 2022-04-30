/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:27:19 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 18:18:45 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

int	check_anomalies(char **mp)
{
	int	x;
	int	y;

	y = 0;
	while (mp[y])
	{	
		x = 0;
		while (mp[y][x])
		{
			if (mp[y][x] != 'C' && mp[y][x] != 'P' && mp[y][x] != 'E'
				&& mp[y][x] != 'X' && mp[y][x] != '0' && mp[y][x] != '1'
				&& mp[y][x] != '\n')
				return (ERROR);
			x++;
		}
		y++;
	}
	return (0);
}

void	check_file(char *name)
{
	int	max;

	max = ft_strlen(name) - 1;
	if (name[max] != 'r' || name[max - 1] != 'e'
		|| name[max - 2] != 'b' || name[max - 3] != '.')
	{
		write(1, "\e[1;91mError\nInvalid file type\n\e[0m", 35);
		exit(1);
	}
}

int	checker(char *map, char ***mp)
{
	int	y;
	int	fd;
	int	i;

	i = 0;
	y = map_y(map);
	if (y < 3)
		errors("\e[1;91mError\nMap is too small\n");
	*mp = malloc((y + 1) * sizeof(char *));
	fd = open(map, O_RDONLY);
	if (!(*mp) || fd == -1)
		errors(strerror(errno));
	(*mp)[i] = get_next_line(fd);
	while ((*mp)[i])
		(*mp)[++i] = get_next_line(fd);
	if (check_len(mp))
		errors("\e[1;91mError\nMap is not rectangular\n\e[0m");
	if (check_walls(mp, y - 1))
		errors("\e[1;91mError\nMap is not closed\n\e[0m");
	if (check_assets(*mp))
		errors("\e[1;91mError\nThere is not enough assets\n\e[0m");
	if (check_anomalies(*mp))
		errors("\e[1;91mError\nThere is an anomaly in your map\n\e[0m");
	return (0);
}

int	check_collectable(t_coord c, t_colist *list)
{
	t_colist	*ptr;

	ptr = list;
	while (ptr && (ptr->c.x != c.x || ptr->c.y != c.y))
		ptr = ptr->next;
	if (ptr && ptr->c.x == c.x && ptr->c.y == c.y)
		return (1);
	return (0);
}
