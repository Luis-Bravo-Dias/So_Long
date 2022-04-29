/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:03:54 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 13:05:07 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

void	start_position(void)
{
	t_coord	c;
	int		trigger;

	c.y = 0;
	trigger = 0;
	while ((*mp())[c.y])
	{
		c.x = 0;
		while ((*mp())[c.y][c.x])
		{
			if ((*mp())[c.y][c.x] == 'P' && trigger)
				(*mp())[c.y][c.x] = '0';
			if ((*mp())[c.y][c.x] == 'P')
				trigger = 1;
			c.x++;
		}
		c.y++;
	}
}

t_coord	find_player(void)
{
	t_coord	c;

	c.y = 0;
	while ((*mp())[c.y])
	{
		c.x = 0;
		while ((*mp())[c.y][c.x])
		{
			if ((*mp())[c.y][c.x] == 'P')
				return (c);
			c.x++;
		}
		c.y++;
	}
	return (c);
}

int	player_colision(int x, int y, char c)
{
	t_coord	pos;

	pos = find_player();
	if ((*mp())[pos.y + y][pos.x + x] != c)
		return (0);
	return (1);
}

void	move_player(int x, int y)
{
	t_coord	c;

	c = find_player();
	if (player_colision(x, y, 'E') && (*game()).collect == 0)
		exit_message("\e[1;95mWelcome, you're back home!\n\e[0m");
	if (x < 0)
		(*game()).play = (*game()).play_l;
	if (x > 0)
		(*game()).play = (*game()).play_r;
	if (player_colision(x, y, 'X'))
		exit_message("\e[1;91mYou couldn't return home...\n\e[0m");
	if (!player_colision(x, y, '1')
		&& !player_colision(x, y, 'E'))
	{
		if (player_colision(x, y, 'C'))
		{
			(*game()).collect--;
			clear_collect(&((*game()).list), c.x + x, c.y + y);
			if (!(*game()).collect)
				(*game()).exit = (*game()).gate;
		}
		(*mp())[c.y][c.x] = '0';
		(*mp())[c.y + y][c.x + x] = 'P';
		(*game()).counter++;
	}
}
