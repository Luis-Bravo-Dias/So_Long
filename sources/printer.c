/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:54:35 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 16:00:58 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/longlib.h"
#include <stdio.h>

size_t	ft_mplen(const char	*str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0' && str[n] != '\n')
		n++;
	return (n);
}

int	map_y(char *map)
{
	int		fd;
	int		line;
	char	c[1];

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		errors("\e[1;91mError\nCouldn't open file\n\e[0m");
		exit(1);
	}
	line = 0;
	while (read(fd, c, 1) != 0)
	{
		if (c[0] == '\n')
			line++;
	}
	if (c[0] != '\n')
		line++;
	close(fd);
	return (line);
}

int	find_char(char **mp, char c)
{
	int	y;
	int	x;

	y = -1;
	while (mp[++y])
	{
		x = -1;
		while (mp[y][++x])
		{
			if (mp[y][x] == c)
				return (0);
		}
	}
	return (ERROR);
}

void	init_sprites(void)
{
	int	s;

	(*game()).play_r = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Player_right.xpm", &s, &s);
	(*game()).play_l = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Player_left.xpm", &s, &s);
	(*game()).doc_r = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Doc_right.xpm", &s, &s);
	(*game()).doc_l = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Doc_left.xpm", &s, &s);
	(*game()).grass = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Grass.xpm", &s, &s);
	(*game()).grave = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Grave.xpm", &s, &s);
	(*game()).gate = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Gate.xpm", &s, &s);
	(*game()).soul = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Soul.xpm", &s, &s);
	(*game()).play = (*game()).play_l;
	(*game()).exit = (*game()).grave;
	(*game()).doc = (*game()).doc_l;
	(*game()).steps = mlx_xpm_file_to_image((*game()).mlx,
			"./Sprites/Steps.xpm", &s, &s);
}

void	print_map(char **mp, t_program *g)
{
	t_coord	c;

	c.y = 0;
	while (mp[c.y / 64])
	{
		c.x = 0;
		while (mp[c.y / 64][c.x / 64])
		{
			if (mp[c.y / 64][c.x / 64] == '1')
				mlx_put_image_to_window((*g).mlx, (*g).w, (*g).grave, c.x, c.y);
			else if (mp[c.y / 64][c.x / 64] == 'P')
				mlx_put_image_to_window((*g).mlx, (*g).w, (*g).play, c.x, c.y);
			else if (mp[c.y / 64][c.x / 64] == 'X')
				mlx_put_image_to_window((*g).mlx, (*g).w, (*g).doc, c.x, c.y);
			else if (mp[c.y / 64][c.x / 64] == 'E')
				mlx_put_image_to_window((*g).mlx, (*g).w, (*g).exit, c.x, c.y);
			else if (mp[c.y / 64][c.x / 64] == 'C')
				mlx_put_image_to_window((*g).mlx, (*g).w, (*g).soul, c.x, c.y);
			else if (mp[c.y / 64][c.x / 64] == '0')
				mlx_put_image_to_window((*g).mlx, (*g).w, (*g).grass, c.x, c.y);
			c.x += 64;
		}
		c.y += 64;
	}
	print_steps();
}
