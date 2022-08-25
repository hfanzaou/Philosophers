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
	printf("%ld ", ft_time() - philo->arg->time);		
	printf("philo %d %s\n", philo->id, s);
	if (pthread_mutex_unlock(&philo->arg->print))
			return ;	
}

void	ft_sleep(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->arg->timelock))
			return ;
	ft_print(philo, "is sleeping");		
	philo->arg->time2 = ft_time();
	if (pthread_mutex_unlock(&philo->arg->timelock))
			return ;
	while (philo->arg->ts >= ft_time() - philo->arg->time2)
		usleep(100);
	ft_print(philo, "is thinking");	
}

int	check_dead(t_philo *philo)
{
	int i;

	i = 0;
	
	// printf("%d\n", args->nph);
	/*if (pthread_mutex_lock(&args->eat))
			return 1;*/	
	if (ft_time() -  philo->arg->time - philo->eat_t >= philo->arg->td /*&& philo->is_eat == 0*/)
	{
		ft_print(philo, "died");
		/*if (pthread_mutex_lock(&args->print))
			return 1;*/
		return (1);
	}
	/*if (pthread_mutex_unlock(&args->eat))
		return 1;*/	
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
		/*if (pthread_mutex_lock(&philo->arg->timelock))
			return (NULL);
		if (philo->arg->time == 0)
			philo->arg->time = ft_time();
		if (pthread_mutex_unlock(&philo->arg->timelock))
			return (NULL);	*/
		ft_print(philo, "takes a fork");
		if (pthread_mutex_lock(&philo->arg->philos[philo->id % philo->arg->nph].fork))
			return (NULL);	
		philo->is_eat = 1;	
		philo->eat_t = ft_time() - philo->arg->time;
		//printf("eat_t = %d \n", philo->eat_t);
		philo->o_eat = ft_time();
		ft_print(philo, "takes a fork");
		ft_print(philo, "is eating");
		while (philo->arg->te > ft_time() - philo->o_eat)
			usleep(100);
		philo->eat_t = ft_time() - philo->arg->time;
		philo->is_eat = 0;	
		if (pthread_mutex_unlock(&philo->arg->philos[philo->id % philo->arg->nph].fork))
			return (NULL);
		if (pthread_mutex_unlock(&philo->fork))
			return (NULL);
		if (check_dead(philo))
			rgit add .eturn (NULL);	
		ft_sleep(philo);
	}	
	return (NULL);
}

int ft_initialize(char **av, t_args *args)
{
	int i;

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
		return (1);
	args->flah_nbr = args->nph;
	args->time = ft_time();
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
	while (i < args->nph)
	{
		pthread_join(args->philos[i].ph, NULL);
		i++;
	}
	return (0);
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
	t_args args;
	if (ac != 5 && ac != 6)
		return (printf("Wrong number of arguments\n"));
	if (check_av(av))
		return (printf("Arguments is not digits\n"));	
	if (ft_initialize(av, &args))
		return (printf("Failed to initialize args\n"));
	// if (check_dead(&args))
	// 	return (0);
}