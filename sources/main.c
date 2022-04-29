/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:56:38 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 12:10:58 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc < 2)
		errors("\e[1;91mError\ntoo few arguments\n\e[0m");
	if (argc > 2)
		errors("\e[1;91mError\ntoo many arguments\n\e[0m");
	check_file(argv[1]);
	checker(argv[1], mp());
	(*game()).mlx = mlx_init();
	(*game()).width = ft_mplen((*mp())[0]);
	(*game()).height = map_y(argv[1]);
	(*game()).w = mlx_new_window((*game()).mlx, (*game()).width * 64,
			(*game()).height * 64, "Soul Catcher");
	init_sprites();
	collectables();
	num_enemies();
	start_position();
	print_map(*mp(), game());
	mlx_key_hook((*game()).w, key, NULL);
	mlx_hook((*game()).w, 17, 0, exit_message,
		(void *)"\e[1;95mSo you give up? What a shame, lost soul.\n\e[0m");
	mlx_loop_hook((*game()).mlx, delay_enemy, NULL);
	mlx_loop((*game()).mlx);
}
