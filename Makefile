# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 16:26:20 by ralves-g          #+#    #+#              #
#    Updated: 2022/04/29 16:34:30 by lleiria-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= @gcc
CFLAGS		= -Wall -Wextra -Werror 
MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

NAME		= so_long

INCLUDE		= get_next_line/get_next_line.h so_long.h
SRCS		= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
				sources/exit.c \
				sources/main.c \
				sources/keys.c \
				sources/steps.c \
				sources/player.c \
				sources/enemies.c \
				sources/collect.c \
				sources/printer.c \
				sources/checker_1.c \
				sources/checker_2.c \
				sources/libft_mini.c \
				sources/enemies_move.c \
				sources/init.c
				
				
OBJS		= $(SRCS:.c=.o)

all:$(NAME)	

$(NAME): $(SRCS) $(OBJS)

			$(CC) $(CFLAGS) $(MLXFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
#			make clean -C $(LIBFT_PATH)
			$(RM) $(OBJS)
#			$(OBJS_B)

fclean:		clean
#			make fclean -C $(LIBFT_PATH)
			$(RM) $(NAME)
#			$(NAME_B)

re:			fclean all