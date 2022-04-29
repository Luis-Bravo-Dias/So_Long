/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:35:24 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 16:27:05 by lleiria-         ###   ########.fr       */
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

t_colist	*new_module(t_coord c)
{
	t_colist	*module;

	module = malloc(sizeof(t_colist));
	if (!module)
		errors("\e[1;91mError\nCouldn't allocate memmory\n\e[0m");
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

/*void	print_list(void)
{
	t_colist	*ptr;
	int			i;

	i = 0;
	ptr = (*game()).list;
	while (ptr)
	{
		printf("x = %d, y = %d\n", ptr->c.x, ptr->c.y);
		ptr = ptr->next;
		i++;
	}
	printf("size = %d\n", i);
}*/

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

int	check_len(char ***mp)
{
	size_t	linelen;
	int		i;

	if (!(*mp))
		return (ERROR);
	i = 1;
	linelen = ft_mplen((*mp)[0]);
	while ((*mp)[i] && linelen == ft_mplen((*mp)[i]))
		i++;
	if (!(*mp)[i])
		return (0);
	return (ERROR);
}

int	check_first(char *line)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(line) - 1;
	while (i < max)
	{
		if (line[i++] != '1')
			return (ERROR);
	}
	if (line[max] != '\n' && line[max] != '1')
		return (ERROR);
	return (0);
}

int	check_vertical(char *line)
{
	int	max;

	max = ft_strlen(line) - 1;
	if (line[0] != '1' || line[max - 1] != '1')
		return (ERROR);
	if (line[max] != '\n')
		return (ERROR);
	return (0);
}

int	check_walls(char ***mp, int y)
{
	int	i;

	i = 1;
	if (check_first((*mp)[0]) || check_first((*mp)[y]))
		return (ERROR);
	while (i < y)
	{
		if (check_vertical((*mp)[i++]))
			return (ERROR);
	}
	return (0);
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

int	check_assets(char **mp)
{
	if (find_char(mp, 'P') || find_char(mp, 'E') || find_char(mp, 'C'))
		return (ERROR);
	return (0);
}

int	check_anomalies(char **mp)
{
	int	x;
	int	y;

	y = 0;
	while (mp[y])
	{	
		x = 0;
		while (mp[y][x])
		{
			if (mp[y][x] != 'C' && mp[y][x] != 'P' && mp[y][x] != 'E'
				&& mp[y][x] != 'X' && mp[y][x] != '0' && mp[y][x] != '1'
				&& mp[y][x] != '\n')
				return (ERROR);
			x++;
		}
		y++;
	}
	return (0);
}

void	check_file(char *name)
{
	int	max;

	max = ft_strlen(name) - 1;
	if (name[max] != 'r' || name[max - 1] != 'e'
		|| name[max - 2] != 'b' || name[max - 3] != '.')
	{
		write(1, "\e[1;91mError\nInvalid file type\n\e[0m", 35);
		exit(1);
	}
}

void	errors(char *message)
{
	if (*mp())
		free_map(mp());
	write(1, message, ft_strlen(message));
	exit(1);
}

int	checker(char *map, char ***mp)
{
	int	y;
	int	fd;
	int	i;

	i = 0;
	y = map_y(map);
	if (y < 3)
		errors("\e[1;91mError\nMap is too small\n");
	*mp = malloc((y + 1) * sizeof(char *));
	fd = open(map, O_RDONLY);
	if (!(*mp) || fd == -1)
		return (ERROR);
	(*mp)[i] = get_next_line(fd);
	while ((*mp)[i])
		(*mp)[++i] = get_next_line(fd);
	if (check_len(mp))
		errors("\e[1;91mError\nMap is not rectangular\n\e[0m");
	if (check_walls(mp, y - 1))
		errors("\e[1;91mError\nMap is not closed\n\e[0m");
	if (check_assets(*mp))
		errors("\e[1;91mError\nThere is not enough assets\n\e[0m");
	if (check_anomalies(*mp))
		errors("\e[1;91mError\nThere is an anomaly in your map\n\e[0m");
	return (0);
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

void	print_steps(void)
{
	char	*steps;

	steps = ft_itoa((*game()).counter);
	mlx_put_image_to_window((*game()).mlx, (*game()).w, (*game()).steps, 0, 0);
	mlx_string_put((*game()).mlx,
		(*game()).w, 86, 3, 0x00000000, steps);
	free(steps);
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

int	check_collectable(t_coord c, t_colist *list)
{
	t_colist	*ptr;

	ptr = list;
	while (ptr && (ptr->c.x != c.x || ptr->c.y != c.y))
		ptr = ptr->next;
	if (ptr && ptr->c.x == c.x && ptr->c.y == c.y)
		return (1);
	return (0);
}

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
		&& !enemy_colision(c, x, y, 'X') /*&& !enemy_colision(c, x, y, 'C')*/)
	{
		if (enemy_colision(c, x, y, 'P'))
			exit_message("\e[1;91mYou couldn't return home...\n\e[0m");
		if (check_collectable(c, (*game()).list))
		{
			printf("collectable at x = %d y = %d\n", c.x, c.y);
			(*mp())[c.y][c.x] = 'C';
		}
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
