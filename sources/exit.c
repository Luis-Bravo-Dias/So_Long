/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:36:14 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 17:15:18 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

void	errors(char *message)
{
	if (*mp())
		free_map(mp());
	write(1, message, ft_strlen(message));
	exit(1);
}

int	exit_message(char *message)
{
	free_map(mp());
	mlx_destroy_image((*game()).mlx, (*game()).play_l);
	mlx_destroy_image((*game()).mlx, (*game()).play_r);
	mlx_destroy_image((*game()).mlx, (*game()).doc_l);
	mlx_destroy_image((*game()).mlx, (*game()).doc_r);
	mlx_destroy_image((*game()).mlx, (*game()).grave);
	mlx_destroy_image((*game()).mlx, (*game()).gate);
	mlx_destroy_image((*game()).mlx, (*game()).grass);
	mlx_destroy_image((*game()).mlx, (*game()).soul);
	mlx_destroy_image((*game()).mlx, (*game()).steps);
	mlx_destroy_window((*game()).mlx, (*game()).w);
	clear_list(&((*game()).list));
	write(1, message, ft_strlen(message));
	exit(0);
	return (0);
}
