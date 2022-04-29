/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:58:20 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 12:10:49 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

int	key(int keycode)
{
	int	steps;

	steps = 0;
	if (keycode == 53)
		exit_message("\e[1;95mSo you give up? What a shame, lost soul.\n\e[0m");
	if (keycode == 13)
		move_player(0, -1);
	if (keycode == 0)
		move_player(-1, 0);
	if (keycode == 1)
		move_player(0, 1);
	if (keycode == 2)
		move_player(1, 0);
	mlx_clear_window((*game()).mlx, (*game()).w);
	print_map(*mp(), game());
	return (0);
}
