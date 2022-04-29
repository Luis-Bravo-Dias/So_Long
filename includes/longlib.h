/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:02:31 by lleiria-          #+#    #+#             */
/*   Updated: 2022/04/29 17:00:43 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LONGLIB_H
# define LONGLIB_H
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>

# include "../get_next_line/get_next_line.h"
# include "../includes/longlib.h"

# define ERROR 1

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_colist
{
	t_coord			c;
	struct s_colist	*next;
}	t_colist;

typedef struct s_program
{
	void		*mlx;
	void		*w;
	int			height;
	int			width;
	int			collect;
	int			enemies;
	int			counter;
	void		*play_r;
	void		*play_l;
	void		*play;
	void		*doc;
	void		*grave;
	void		*grass;
	void		*gate;
	void		*exit;
	void		*doc_r;
	void		*doc_l;
	void		*soul;
	void		*steps;
	t_colist	*list;
}	t_program;

t_program	*game(void);
char		***mp(void);
void		free_map(char ***mp);
void		errors(char *message);
int			exit_message(char *message);
size_t		ft_strlen(const char	*str);
char		*ft_itoa(int n);
int			key(int keycode);
void		num_enemies(void);
int			enemy_colision(t_coord c, int x, int y, char asset);
t_coord		find_enemy(int i, char **map);
void		move_enemy(t_coord c, int x, int y);
void		move_every_enemy(void);
int			delay_enemy(void);
int			check_len(char ***mp);
int			check_first(char *line);
int			check_vertical(char *line);
int			check_walls(char ***mp, int y);
int			check_assets(char **mp);
int			check_anomalies(char **mp);
void		check_file(char *name);
int			checker(char *map, char ***mp);
int			check_collectable(t_coord c, t_colist *list);
void		print_steps(void);
void		start_position(void);
t_coord		find_player(void);
int			player_colision(int x, int y, char c);
void		move_player(int x, int y);
t_colist	*new_module(t_coord c);
void		addlast(t_colist **list, t_colist *new);
void		clear_collect(t_colist **list, int x, int y);
void		clear_list(t_colist **list);
void		collectables(void);
size_t		ft_mplen(const char	*str);
int			map_y(char *map);
int			find_char(char **mp, char c);
void		init_sprites(void);
void		print_map(char **mp, t_program *g);

#endif