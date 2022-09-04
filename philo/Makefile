# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 22:06:23 by hfanzaou          #+#    #+#              #
#    Updated: 2022/08/05 22:06:25 by hfanzaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo.c srcs/ft_initialize.c srcs/utils.c srcs/check_exit.c srcs/utils2.c
OSRCS = $(SRCS:.c=.o)		
NAME = philo
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread
CC = gcc

all : $(NAME)

$(NAME)	: $(OSRCS)
	$(CC) $(CFLAGS) $(OSRCS) -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OSRCS)

fclean : clean
	rm -rf $(NAME)

re : fclean all