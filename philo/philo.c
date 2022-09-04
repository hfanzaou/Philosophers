/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 22:04:04 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/02 03:16:27 by hfanzaou         ###   ########.fr       */
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

int	ft_eat(t_philo *philo)
{
	long	time;

	if (change_lock(&philo->eat_t, philo, ft_time() - philo->arg->time))
		return (1);
	time = ft_time();
	if (change_lock(&philo->is_eat, philo, 1))
		return (1);
	ft_print(philo, "is eating");
	while (philo->arg->te > ft_time() - time)
		usleep(100);
	if (change_lock(&philo->is_eat, philo, 0))
		return (1);
	if (change_lock(&philo->nofmeals, philo, philo->nofmeals + 1))
		return (1);
	return (0);
}

int	ft_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork))
		return (1);
	ft_print(philo, "takes a fork");
	if (pthread_mutex_lock(&philo->arg->philos
			[philo->id % philo->arg->nph].fork))
		return (1);
	ft_print(philo, "takes a fork");
	if (ft_eat(philo))
		return (1);
	if (pthread_mutex_unlock(&philo->arg->philos
			[philo->id % philo->arg->nph].fork))
		return (1);
	if (pthread_mutex_unlock(&philo->fork))
		return (1);
	return (0);
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (ft_forks(philo))
			return (NULL);
		if (philo->nofmeals == philo->arg->nof)
		{
			ft_print(philo, "is done");
			return (NULL);
		}
		if (ft_sleep(philo))
			return (NULL);
	}	
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac != 5 && ac != 6)
		return (printf("Wrong number of arguments\n"));
	if (check_av(av))
		return (printf("Arguments is not digits\n"));
	args = ft_initialize(av);
	if (!args)
	{
		free(args);
		return (printf("Failed to initialize args\n"));
	}
	if (check_exit(args->philos))
	{
		free(args);
		return (0);
	}
}
