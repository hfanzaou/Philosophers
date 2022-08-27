/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 22:04:04 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/08/05 22:04:07 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	check_av(char **av)
{
	int	i;
	int	j;

	 i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;	
		}
		i++;
	}
	return (0);
}

long ft_time()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_print(t_philo *philo, const char *s)
{
	if (pthread_mutex_lock(&philo->arg->print))
			return ;
	/*if (pthread_mutex_lock(&philo->arg->deadlock))
		return ;*/		
	if (philo->arg->dead == 0)
		return ;
	/*if (pthread_mutex_lock(&philo->arg->deadlock))
		return ;*/
	printf("%ld ", ft_time() - philo->arg->time);		
	printf("philo %d %s\n", philo->id, s);
	if (pthread_mutex_unlock(&philo->arg->print))
			return ;	
}

int	check_dead(t_philo *philo)
{
	int i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < philo->arg->nph)
		{
			if ((ft_time() -  philo->arg->time - philo[i].eat_t >= philo->arg->td) && philo[i].is_eat == 0)
			{
				ft_print(&philo[i], "died");
				/*if (pthread_mutex_lock(&philo->arg->deadlock))
					return (1);*/
				philo->arg->dead = 0;
				/*if (pthread_mutex_unlock(&philo->arg->deadlock))
					return (1);*/
				
				return (1);
			}
			i++;
		}
	}
	return (0);
}



int	ft_sleep(t_philo *philo)
{
	long	time;
 
	ft_print(philo, "is sleeping");
	time = ft_time();
	while (philo->arg->ts > ft_time() - time)
	{
		/*if (pthread_mutex_lock(&philo->arg->deadlock))
			return (1);*/
		if (philo->arg->dead == 0)
			return (1);
		/*if (pthread_mutex_lock(&philo->arg->deadlock))
			return (1);*/
		usleep(100);
	}
	ft_print(philo, "is thinking");
	return (0);	
}



void *routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		if (pthread_mutex_lock(&philo->fork))
			return (NULL);
		ft_print(philo, "takes a fork 1");
		if (pthread_mutex_lock(&philo->arg->philos[philo->id % philo->arg->nph].fork))
			return (NULL);	
		philo->is_eat = 1;	
		philo->eat_t = ft_time() - philo->arg->time;
		philo->o_eat = ft_time();
		ft_print(philo, "takes a fork 2");
		ft_print(philo, "is eating");
		while (philo->arg->te > ft_time() - philo->o_eat)
		{
			/*if (pthread_mutex_lock(&philo->arg->deadlock))
				return (NULL);*/
			if (philo->arg->dead == 0)
				return (NULL);
			/*if (pthread_mutex_lock(&philo->arg->deadlock))
				return (NULL);*/
			usleep(100);
		}
		philo->is_eat = 0;	
		if (pthread_mutex_unlock(&philo->arg->philos[philo->id % philo->arg->nph].fork))
			return (NULL);
		if (pthread_mutex_unlock(&philo->fork))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
	}	
	return (NULL);
}

t_args *ft_initialize(char **av)
{
	int i;
	t_args *args;

	i = 0;
	args = malloc(sizeof(t_args));
	args->nph = ft_atoi(av[1]);
	//printf("%d\n", args->nph);
	args->td = ft_atoi(av[2]);
	args->te = ft_atoi(av[3]);
	args->ts = ft_atoi(av[4]);
	if (av[5])
		args->ne = ft_atoi(av[5]);
	if (!(args->philos = malloc(sizeof(t_philo) * args->nph)))
		return (NULL);
	args->flah_nbr = args->nph;
	args->time = ft_time();
	args->dead = 1;
	while (i < args->nph)
	{
		args->philos[i].o_eat = 0;
		args->philos[i].is_eat = 0;
		args->philos[i].eat_t = 0;
		args->philos[i].id = i + 1;
		args->philos[i].arg = args;
		pthread_mutex_init(&args->philos[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&args->timelock, NULL);
	pthread_mutex_init(&args->print, NULL);
	i = 0;
	while (i < args->nph)
	{
		pthread_create(&args->philos[i].ph, NULL, routine, &args->philos[i]);
		usleep(10);
		i++;
	}
	i = 0;
	/*
	while (i < args->nph)
	{
		//void *k;
		pthread_join(args->philos[i].ph, NULL);
		i++;
	}*/
	return (args);
}

// int	check_dead(t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (1)
// 	{
// 		// printf("%d\n", args->nph);
// 		/*if (pthread_mutex_lock(&args->eat))
// 				return 1;*/	
// 		if (ft_time() -  philo->arg->time - philo->eat_t > philo->arg->td && philo->is_eat == 0)
// 		{
// 			ft_print(philo, "died");
// 			/*if (pthread_mutex_lock(&args->print))
// 				return 1;*/
// 			return (1);
// 		}
// 		/*if (pthread_mutex_unlock(&args->eat))
// 			return 1;*/	
// 	}
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_args *args;
	if (ac != 5 && ac != 6)
		return (printf("Wrong number of arguments\n"));
	if (check_av(av))
		return (printf("Arguments is not digits\n"));	
	if (!(args = ft_initialize(av)))
		return (printf("Failed to initialize args\n"));
	if (check_dead(args->philos))
		return (0);
}