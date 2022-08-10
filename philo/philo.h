/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 22:05:03 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/08/05 22:05:05 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
struct s_args;

typedef struct s_philo
{
	pthread_t	ph;
	int			id;
	int			eat_t;
	pthread_mutex_t			fork;
	struct s_args *arg;
}	t_philo;

typedef struct s_args
{
	int	nph;
	int	td;
	int	te;
	int	ts;
	int	ne;
	int curr_t;
	int fi_t;
	long time;
	t_philo *philos;
}	t_args;

int				ft_isdigit(int c);
long long int	ft_atoi(const char *str);
# endif