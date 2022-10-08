/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 04:58:56 by hermesrolle       #+#    #+#             */
/*   Updated: 2022/10/08 14:14:23 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	my_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	mufork_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->all->mufork[philo->n_philo - 1]);
	if (philo->n_philo >= philo->all->philos)
		pthread_mutex_unlock(&philo->all->mufork[0]);
	else
		pthread_mutex_unlock(&philo->all->mufork[philo->n_philo]);
	return (1);
}

int	print_death(t_philo *philo, unsigned long time)
{
	pthread_mutex_lock(&philo->all->pencil);
	if (philo->all->death)
	{
		pthread_mutex_unlock(&philo->all->pencil);
		return (1);
	}
	philo->all->death = 1;
	printf("%lu : philo %u is dead\n", time - philo->all->start_time, philo->n_philo);
	pthread_mutex_unlock(&philo->all->pencil);
	return (1);
}

int	print_action(t_philo *philo, char *s, unsigned long time)
{
	pthread_mutex_lock(&philo->all->pencil);
	if (philo->all->death)
	{
		pthread_mutex_unlock(&philo->all->pencil);
		return (1);
	}
	if (my_time() - philo->is_dead >= philo->all->death_time)
		return (print_death(philo, time));
	printf("%lu : philo %u %s\n", time - philo->all->start_time, philo->n_philo, s);
	pthread_mutex_unlock(&philo->all->pencil);
	return (0);
}

int	take_fork_a(t_philo *philo, unsigned long *time)
{
	pthread_mutex_lock(&philo->all->mufork[philo->n_philo - 1]);
	*time = my_time();
	if (print_action(philo, "take a fork", *time))
	{
		pthread_mutex_lock(&philo->all->mufork[philo->n_philo - 1]);
		return (1);
	}
	if (my_time() - philo->is_dead >= philo->all->death_time)
	{
		pthread_mutex_unlock(&philo->all->mufork[philo->n_philo - 1]);
		return (print_death(philo, *time));
	}
	if (philo->n_philo >= philo->all->philos)
		pthread_mutex_lock(&philo->all->mufork[0]);
	else
		pthread_mutex_lock(&philo->all->mufork[philo->n_philo]);
	if (print_action(philo, "take a fork", *time))
		return (mufork_unlock(philo));
	if (my_time() - philo->is_dead >= philo->all->death_time)
	{
		mufork_unlock(philo);
		return (print_death(philo, *time));
	}
	return (0);
}

int	take_fork_b(t_philo *philo, unsigned long *time)
{
	int	num;

	if (philo->n_philo >= philo->all->philos)
		num = 0;
	else
		num = philo->n_philo;
	pthread_mutex_lock(&philo->all->mufork[num]);
	*time = my_time();
	if (print_action(philo, "take a fork", *time))
	{
		pthread_mutex_unlock(&philo->all->mufork[num]);
		return (1);
	}
	if (my_time() - philo->is_dead >= philo->all->death_time)
	{
		pthread_mutex_unlock(&philo->all->mufork[num]);
		return (print_death(philo, *time));
	}
	pthread_mutex_lock(&philo->all->mufork[philo->n_philo - 1]);
	if (print_action(philo, "take a fork", *time))
		return (mufork_unlock(philo));
	if (my_time() - philo->is_dead >= philo->all->death_time)
	{
		mufork_unlock(philo);
		return (print_death(philo, *time));
	}
	return (0);
}

int		eating(t_philo *philo)
{
	unsigned long	time;

	//if (philo->all->each_eat_time && philo->each_eat_time >= philo->all->each_eat_time)
	//	return (1);
	time = my_time();
	if (print_action(philo, "is thinking", time))
		return (1);
	if (philo->n_philo % 2)
	{
		if (take_fork_a(philo, &time))
			return (1);
	}
	else
		if (take_fork_b(philo, &time))
			return (1);
	time = my_time();
	philo->is_dead = time;
	if (print_action(philo, "is eating", time))
		return (mufork_unlock(philo));
	while (my_time() - time < philo->all->eat_time)
	{
		if (my_time() - philo->is_dead >= philo->all->death_time)
		{
			mufork_unlock(philo);
			return (print_death(philo, time));
		}
		usleep(10);
	}
	//philo->each_eat_time++;
	mufork_unlock(philo);
	return (0);
}

int		sleeping(t_philo *philo)
{
	unsigned long	time;

	time = my_time();
	if (print_action(philo, "is sleeping", time))
		return (1);
	while (my_time() - time < philo->all->sleep_time)
	{
		if (my_time() - philo->is_dead >= philo->all->death_time)
			return (print_death(philo, time));
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
		if (eating(my_philo))
			return (NULL);
		else if (sleeping(my_philo))
			return (NULL);
	}
}
