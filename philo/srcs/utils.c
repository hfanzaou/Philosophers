/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:56:54 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/04 04:11:20 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_print(t_philo *philo, const char *s)
{
	if (pthread_mutex_lock(&philo->arg->print))
		return (1);
	printf("%ld ", ft_time() - philo->arg->time);
	printf("philo %d %s\n", philo->id, s);
	if (ft_strcmp("died", s) && philo->arg->count != philo->arg->nph)
	{
		if (pthread_mutex_unlock(&philo->arg->print))
			return (0);
	}
	return (1);
}

long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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

int	change_lock(int *i, t_philo *philo, int va)
{	
	if (pthread_mutex_lock(&philo->arg->arg))
		return (1);
	*i = va;
	if (pthread_mutex_unlock(&philo->arg->arg))
		return (1);
	return (0);
}
