/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:03:12 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 12:10:20 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

void	num_enemies(void)
{
	t_coord	c;

	(*game()).enemies = 0;
	c.y = 0;
	while ((*mp())[c.y])
	{
		c.x = 0;
		while ((*mp())[c.y][c.x])
		{
			if ((*mp())[c.y][c.x] == 'X')
				(*game()).enemies++;
			c.x++;
		}
		c.y++;
	}
}

int	enemy_colision(t_coord c, int x, int y, char asset)
{
	if ((*mp())[c.y + y][c.x + x] != asset)
		return (0);
	return (1);
}

t_coord	find_enemy(int i, char **map)
{
	t_coord	c;

	c.y = 0;
	while (map[c.y])
	{
		c.x = 0;
		while (map[c.y][c.x])
		{
			if (map[c.y][c.x] == 'X' && !i)
				return (c);
			if (map[c.y][c.x] == 'X')
				i--;
			c.x++;
		}
		c.y++;
	}
	return (c);
}
