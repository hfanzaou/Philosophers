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

SRCS = srcs/ft_atoi.c srcs/ft_isdigit.c srcs/philo.c srcs/ft_initialize.c 
		srcs/utils.c srcs/check_death.c
OSRCS = $(SRCS:.c=.o)		
NAME = philo
CFLAGS = -Wall -Werror -Wextra
CC = gcc

all : $(NAME) $(OSRCS)

$(NAME) : $(OSRCS)
	
$(OSRCS) : $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -c $@ -o $(NAME) 

