/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                      :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:02:22 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/04 04:11:00 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	check_death(t_philo *philo)
{
	if ((ft_time() - philo->arg->time - philo->eat_t >= philo->arg->td)
		&& philo->is_eat == 0)
	{
		ft_print(philo, "died");
		return (1);
	}
	return (0);
}

int	check_exit(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		philo->arg->count = 0;
		while (i < philo->arg->nph)
		{
			if (pthread_mutex_lock(&philo->arg->arg))
				return (1);
			if (check_death(&philo[i]))
				return (1);
			if (philo[i].nofmeals == philo->arg->nof)
			{
				if (++philo->arg->count == philo->arg->nph)
					return (1);
			}
			if (pthread_mutex_unlock(&philo->arg->arg))
				return (1);
			i++;
		}
	}
	return (0);
}
