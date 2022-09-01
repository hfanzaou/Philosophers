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

int	ft_print(t_philo *philo, const char *s)
{
	if (pthread_mutex_lock(&philo->arg->print))
			return (1);
	printf("%ld ", ft_time() - philo->arg->time);		
	printf("philo %d %s\n", philo->id, s);
	if (strcmp("died", s) || philo->arg->all_eat != philo->arg->nph)
	{
		if (pthread_mutex_unlock(&philo->arg->print))
			return (1);
	}
	return (0);	
}

int if_all_eat(t_philo *philo)
{
	int i;
	int l;

	l = 0;
	i = 0;
	while (i < philo->arg->nph)
	{
		if (philo[i].nofmeals >= philo->arg->ne)
			l++;
		i++;	
	}
	philo->arg->all_eat = l;
	return (l);
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
			if (pthread_mutex_lock(&philo->arg->arg))
				return (1);
			if ((ft_time() -  philo->arg->time - philo[i].eat_t >= philo->arg->td) && philo[i].is_eat == 0)
			{
				if (pthread_mutex_unlock(&philo->arg->arg))
					return (1);
				ft_print(&philo[i], "died");
				return (1);
			}
			if (if_all_eat(philo) == philo->arg->nph)
				return (1);
			if (pthread_mutex_unlock(&philo->arg->arg))
					return (1);
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
		usleep(100);
	ft_print(philo, "is thinking");
	return (0);	
}
int	change_lock(int *i, t_args *args, int va)
{
	if (pthread_mutex_lock(&args->arg))
		return (1);
	*i = va;
	if (pthread_mutex_unlock(&args->arg))
		return (1);
	return (0);		
}

int	ft_eat(t_philo *philo)
{
	if (change_lock(&philo->eat_t, philo->arg, ft_time() - philo->arg->time))
		return (1);	
	philo->o_eat = ft_time();
	if (change_lock(&philo->is_eat, philo->arg, 1))
		return (1);
	ft_print(philo, "is eating");
	while (philo->arg->te > ft_time() - philo->o_eat)
		usleep(100);
	if (change_lock(&philo->is_eat, philo->arg, 0))
		return (1);
	if (change_lock(&philo->nofmeals, philo->arg, philo->nofmeals + 1))
		return (1);
	return (0);
}
void *routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (pthread_mutex_lock(&philo->fork))
			return (NULL);
		ft_print(philo, "takes a fork 1");
		if (pthread_mutex_lock(&philo->arg->philos[philo->id % philo->arg->nph].fork))
			return (NULL);
		ft_print(philo, "takes a fork 2");
		if (ft_eat(philo))
			return (NULL);
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
	args->td = ft_atoi(av[2]);
	args->te = ft_atoi(av[3]);
	args->ts = ft_atoi(av[4]);
	if (av[5])
		args->ne = ft_atoi(av[5]);
	else
		args->ne = -1;	
	if (!(args->philos = malloc(sizeof(t_philo) * args->nph)))
		return (NULL);
	args->time = ft_time();
	while (i < args->nph)
	{
		args->philos[i].nofmeals = 0;
		args->philos[i].o_eat = 0;
		args->philos[i].is_eat = 0;
		args->philos[i].eat_t = 0;
		args->philos[i].id = i + 1;
		args->philos[i].arg = args;
		pthread_mutex_init(&args->philos[i].fork, NULL);
		i++;
	}
	pthread_mutex_init(&args->arg, NULL);
	pthread_mutex_init(&args->timelock, NULL);
	pthread_mutex_init(&args->print, NULL);
	i = 0;
	while (i < args->nph)
	{
		pthread_create(&args->philos[i].ph, NULL, routine, &args->philos[i]);
		pthread_detach(args->philos[i].ph);
		usleep(10);
		i++;
	}
	return (args);
}

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