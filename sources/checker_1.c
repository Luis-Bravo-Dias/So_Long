/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:17:13 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 12:28:08 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

int	check_len(char ***mp)
{
	size_t	linelen;
	int		i;

	if (!(*mp))
		return (ERROR);
	i = 1;
	linelen = ft_mplen((*mp)[0]);
	while ((*mp)[i] && linelen == ft_mplen((*mp)[i]))
		i++;
	if (!(*mp)[i])
		return (0);
	return (ERROR);
}

int	check_first(char *line)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(line) - 1;
	while (i < max)
	{
		if (line[i++] != '1')
			return (ERROR);
	}
	if (line[max] != '\n' && line[max] != '1')
		return (ERROR);
	return (0);
}

int	check_vertical(char *line)
{
	int	max;

	max = ft_strlen(line) - 1;
	if (line[0] != '1' || line[max - 1] != '1')
		return (ERROR);
	if (line[max] != '\n')
		return (ERROR);
	return (0);
}

int	check_walls(char ***mp, int y)
{
	int	i;

	i = 1;
	if (check_first((*mp)[0]) || check_first((*mp)[y]))
		return (ERROR);
	while (i < y)
	{
		if (check_vertical((*mp)[i++]))
			return (ERROR);
	}
	return (0);
}

int	check_assets(char **mp)
{
	if (find_char(mp, 'P') || find_char(mp, 'E') || find_char(mp, 'C'))
		return (ERROR);
	return (0);
}
