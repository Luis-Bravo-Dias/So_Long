/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:10:44 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 17:05:13 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

t_colist	*new_module(t_coord c)
{
	t_colist	*module;

	module = malloc(sizeof(t_colist));
	if (!module)
		errors(strerror(errno));
	module->c = c;
	module->next = NULL;
	return (module);
}

void	addlast(t_colist **list, t_colist *new)
{
	t_colist	*ptr;

	ptr = *list;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	clear_collect(t_colist **list, int x, int y)
{
	t_colist	*ptr;
	t_colist	*tmp;
	int			i;

	i = 0;
	ptr = *list;
	tmp = *list;
	while (ptr->c.x != x || ptr->c.y != y)
	{
		ptr = ptr->next;
		i++;
	}
	while (i > 1)
	{
		tmp = tmp->next;
		i--;
	}
	if (i == 0)
		*list = ptr->next;
	else
		tmp->next = ptr->next;
	free(ptr);
}

void	clear_list(t_colist **list)
{
	t_colist	*ptr;

	if (!(*list) || !list)
		return ;
	while (*list)
	{
		ptr = (*list)->next;
		free(*list);
		*list = ptr;
	}
}

void	collectables(void)
{
	t_coord	c;

	(*game()).collect = 0;
	(*game()).list = NULL;
	c.y = 0;
	while ((*mp())[c.y])
	{
		c.x = 0;
		while ((*mp())[c.y][c.x])
		{
			if ((*mp())[c.y][c.x] == 'C')
			{
				(*game()).collect++;
				addlast(&((*game()).list), new_module(c));
			}
			c.x++;
		}
		c.y++;
	}
}
