/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:02:22 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/02 03:02:41 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	if_all_eat(t_philo *philo)
{
	int	i;
	int	l;

	l = 0;
	i = 0;
	if (philo->arg->ne == -1)
		return (0);
	while (i < philo->arg->nph)
	{
		if (philo[i].nofmeals >= philo->arg->ne)
			l++;
		i++;
	}
	return (l);
}

int	check_death(t_philo *philo)
{
	if ((ft_time() - philo->arg->time - philo->eat_t >= philo->arg->td)
		&& philo->is_eat == 0)
	{
		if (pthread_mutex_unlock(&philo->arg->arg))
			return (1);
		ft_print(philo, "died");
		return (1);
	}
	return (0);
}

int	check_exit(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < philo->arg->nph)
		{
			if (pthread_mutex_lock(&philo->arg->arg))
				return (1);
			if (check_death(&philo[i]))
				return (1);
			if (if_all_eat(philo) == philo->arg->nph)
				return (1);
			if (pthread_mutex_unlock(&philo->arg->arg))
				return (1);
			i++;
		}
	}
	return (0);
}
