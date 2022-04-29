/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:41:25 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 12:57:45 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

void	print_steps(void)
{
	char	*steps;

	steps = ft_itoa((*game()).counter);
	mlx_put_image_to_window((*game()).mlx, (*game()).w, (*game()).steps, 0, 0);
	mlx_string_put((*game()).mlx,
		(*game()).w, 86, 3, 0x00000000, steps);
	free(steps);
}
