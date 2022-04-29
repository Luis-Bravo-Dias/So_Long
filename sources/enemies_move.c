/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:09:12 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 16:28:08 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

void	move_enemy(t_coord c, int x, int y)
{
	if (x == 2)
		x = -1;
	if (y == 2)
		y = -1;
	if (x < 0)
		(*game()).doc = (*game()).doc_l;
	if (x > 0)
		(*game()).doc = (*game()).doc_r;
	if (!enemy_colision(c, x, y, '1') && !enemy_colision(c, x, y, 'E')
		&& !enemy_colision(c, x, y, 'X'))
	{
		if (enemy_colision(c, x, y, 'P'))
			exit_message("\e[1;91mYou couldn't return home...\n\e[0m");
		if (check_collectable(c, (*game()).list))
			(*mp())[c.y][c.x] = 'C';
		else
			(*mp())[c.y][c.x] = '0';
		(*mp())[c.y + y][c.x + x] = 'X';
	}
}

void	move_every_enemy(void)
{
	char	**map;
	int		i;

	map = *mp();
	i = 0;
	while (i < (*game()).enemies)
	{
		move_enemy(find_enemy(i, map), rand() % 3, rand() % 3);
		i++;
	}
}

int	delay_enemy(void)
{
	static int	delay;

	if (delay < 5000)
	{
		delay++;
		return (0);
	}
	delay = 0;
	move_every_enemy();
	mlx_clear_window((*game()).mlx, (*game()).w);
	print_map(*mp(), game());
	return (0);
}
