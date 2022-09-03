/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:33:55 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/02 02:34:26 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

t_args	*init_args(char **av)
{
	t_args	*args;
	int		i;

	i = 0;
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->nph = ft_atoi(av[1]);
	args->td = ft_atoi(av[2]);
	args->te = ft_atoi(av[3]);
	args->ts = ft_atoi(av[4]);
	if (av[5])
		args->ne = ft_atoi(av[5]);
	else
		args->ne = -1;
	args->time = ft_time();
	return (args);
}

t_philo	*init_philos(t_args *args)
{	
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->nph);
	if (!philos)
		return (NULL);
	while (i < args->nph)
	{
		philos[i].nofmeals = 0;
		philos[i].is_eat = 0;
		philos[i].eat_t = 0;
		philos[i].id = i + 1;
		philos[i].arg = args;
		if (pthread_mutex_init(&philos[i].fork, NULL))
			return (NULL);
		i++;
	}
	return (philos);
}

int	init_mutex(t_args *args)
{
	if (pthread_mutex_init(&args->arg, NULL))
		return (1);
	if (pthread_mutex_init(&args->timelock, NULL))
		return (1);
	if (pthread_mutex_init(&args->print, NULL))
		return (1);
	return (0);
}

t_args	*ft_initialize(char **av)
{
	int		i;
	t_args	*args;

	args = init_args(av);
	if (!args)
		return (NULL);
	args->philos = init_philos(args);
	if (!args->philos)
		return (NULL);
	if (init_mutex(args))
		return (NULL);
	i = 0;
	while (i < args->nph)
	{
		if (pthread_create(&args->philos[i].ph, NULL,
				routine, &args->philos[i]))
			return (NULL);
		if (pthread_detach(args->philos[i].ph))
			return (NULL);
		usleep(10);
		i++;
	}
	return (args);
}
