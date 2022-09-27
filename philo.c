/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 04:58:56 by hermesrolle       #+#    #+#             */
/*   Updated: 2022/09/27 19:50:42 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	my_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int		eating(t_philo *philo)
{
	unsigned long	time;

	//if (philo->all->each_eat_time && philo->each_eat_time >= philo->all->each_eat_time)
	//	return (1);
	if (philo->all->death)
		return (1);
	time = my_time();
	printf("%lu : philo %u is thinking\n", time - philo->all->start_time, philo->n_philo);
	pthread_mutex_lock(&philo->all->mufork[philo->n_philo - 1]);
	if (philo->all->death)
		return (1);
	printf("%lu : philo %u take a fork\n", time - philo->all->start_time, philo->n_philo);
	if (my_time() - time  >= philo->all->death_time - philo->all->sleep_time)//philo->all->death_time - philo->all->sleep_time
	{
		philo->all->death = 1;
		printf("%lu : philo %u is dead\n", time - philo->all->start_time, philo->n_philo);
		return (1);
	}
	if (philo->all->death)
		return (1);
	if (philo->n_philo >= philo->all->philos)
		pthread_mutex_lock(&philo->all->mufork[0]);
	else
		pthread_mutex_lock(&philo->all->mufork[philo->n_philo]);
	printf("%lu : philo %u take a fork\n", time - philo->all->start_time, philo->n_philo);
	if (my_time() - time >= philo->all->death_time - philo->all->sleep_time)//philo->all->death_time - philo->all->sleep_time
	{
		philo->all->death = 1;
		printf("%lu : philo %u is dead\n", time - philo->all->start_time, philo->n_philo);
		return (1);
	}
	if (philo->all->death)
		return (1);
	time = my_time();
	printf("%lu : philo %u is eating\n", time - philo->all->start_time, philo->n_philo);
	while (my_time() - time < philo->all->eat_time)
	{
		if (philo->all->death)
			return (1);
		usleep(10);
	}
	//philo->each_eat_time++;
	pthread_mutex_unlock(&philo->all->mufork[philo->n_philo - 1]);
	if (philo->n_philo >= philo->all->philos)
		pthread_mutex_unlock(&philo->all->mufork[0]);
	else
		pthread_mutex_unlock(&philo->all->mufork[philo->n_philo]);
	return (0);
}

int		sleeping(t_philo *philo)
{
	unsigned long	time;

	if (philo->all->death)
		return (1);
	time = my_time();
	printf("%lu : philo %u is sleeping\n", time - philo->all->start_time, philo->n_philo);
	while (my_time() - time < philo->all->sleep_time)
	{
		if (philo->all->death)
			return (1);
		usleep(10);
	}
	return (0);
}

void	*philo_func(void *philo)
{
	t_philo	*my_philo;

	my_philo = (t_philo *)philo;
	while (1)
	{
		if (my_philo->all->death)
			return (NULL);
		if (eating(my_philo))
			return (NULL);
		if (sleeping(my_philo))
			return (NULL);
	}
}

// t_philo	*philo_create()
// {
// 	t_philo	*philo;

// 	philo = ft_calloc(1, sizeof(*philo));
// 	philo->all = malloc(...);
// 	return (philo);
// }

// void	philo_destroy(t_philo **philo)
// {
// 	t_philo	*p;

// 	p = *philo;
// 	all_destroy();
// 	free(p);
// 	*philo = NULL;
// }