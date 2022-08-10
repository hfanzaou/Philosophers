/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
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

void *routine(void *philos)
{
	t_philo philo;

	philo = *(t_philo *)philos;
	if (pthread_mutex_lock(&philo.fork))
		return (NULL);
	if (pthread_mutex_lock(&philo.arg->philos[philo.id % philo.arg->nph].fork))
		return (NULL);
	usleep(100000);	
	philo.eat_t = ft_time() - philo.arg->time;
	printf("%d ", philo.eat_t);	
	printf("%d takes the fork %d\ntakes the fork %d\n", philo.id, philo.id, philo.id % philo.arg->nph + 1);
	printf("%d is eating\n", philo.id);
	while (philo.eat_t > ft_time() - philo.arg->time)
	if (pthread_mutex_unlock(&philo.fork))
		return (NULL);
	if (pthread_mutex_unlock(&philo.arg->philos[philo.id % philo.arg->nph].fork))
		return (NULL);
	return (NULL);
}

int ft_initialize(char **av, t_args *args)
{
	int i;

	i = 0;
	args->nph = ft_atoi(av[1]);
	printf("%d\n", args->nph);
	args->td = ft_atoi(av[2]);
	args->te = ft_atoi(av[3]);
	args->ts = ft_atoi(av[4]);
	if (av[5])
		args->ne = ft_atoi(av[5]);
	args->philos = malloc(sizeof(t_philo) * args->nph);
	args->time = ft_time();
	printf("%ld\n", args->time);
	while (i < args->nph)
	{
		args->philos[i].eat_t = 0;
		args->philos[i].id = i + 1;
		args->philos[i].arg = args;
		pthread_mutex_init(&args->philos[i].fork, NULL);
		i++;
	}
	i = 0;
	while (i < args->nph)
	{
		pthread_create(&args->philos[i].ph, NULL, routine, &args->philos[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < args->nph)
	{
		pthread_join(args->philos[i].ph, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args args;
	if (ac != 5 && ac != 6)
		return (printf("Wrong number of arguments\n"));
	if (check_av(av))
		return (printf("Arguments is not digits\n"));	
	if (ft_initialize(av, &args))
		return (printf("Failed to initialize args\n"));
}