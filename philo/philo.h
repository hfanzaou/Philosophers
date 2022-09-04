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

struct	s_args;

typedef struct s_philo
{
	pthread_t		ph;
	int				id;
	int				eat_t;
	int				is_eat;
	int				nofmeals;
	pthread_mutex_t	fork;
	struct s_args	*arg;
}					t_philo;

typedef struct s_args
{
	int				nph;
	int				td;
	int				te;
	int				ts;
	int				nof;
	int				count;
	long			time;
	pthread_mutex_t	print;
	pthread_mutex_t	timelock;
	t_philo			*philos;
	pthread_mutex_t	arg;
}					t_args;

//philos//
t_args	*ft_initialize(char **av);
void	*routine(void *philos);

//supervisor//
int		check_exit(t_philo *philo);

//Utils//
long	ft_time(void);
int		ft_print(t_philo *philo, const char *s);
int		ft_sleep(t_philo *philo);
int		change_lock(int *i, t_philo *philo, int va);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
#endif
