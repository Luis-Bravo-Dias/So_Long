/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:05:42 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 16:06:19 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

t_program	*game(void)
{
	static t_program	soul_catcher;

	return (&soul_catcher);
}

char	***mp(void)
{
	static char	**ismap;

	return (&ismap);
}

void	free_map(char ***mp)
{
	int	i;

	i = 0;
	if (*mp)
	{
		while ((*mp)[i])
		{
			free((*mp)[i++]);
		}
		free(*mp);
	}
}
