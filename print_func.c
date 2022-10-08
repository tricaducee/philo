/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:33:00 by hrolle            #+#    #+#             */
/*   Updated: 2022/10/08 22:33:01 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_death(t_philo *philo, unsigned long time)
{
	pthread_mutex_lock(&philo->all->pencil);
	if (philo->all->death)
	{
		pthread_mutex_unlock(&philo->all->pencil);
		return (1);
	}
	philo->all->death = 1;
	printf("%-7lu : philo %2u is dead\n",
		time - philo->all->start_time, philo->n_philo);
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
	{
		pthread_mutex_unlock(&philo->all->pencil);
		return (print_death(philo, time));
	}
	if (philo->each_eat_time)
		printf("%-7lu : philo %2u %-16s |  has to eat %u more times\n",
			time - philo->all->start_time,
			philo->n_philo, s, philo->each_eat_time - 1);
	else
		printf("%-7lu : philo %2u %s\n",
			time - philo->all->start_time, philo->n_philo, s);
	pthread_mutex_unlock(&philo->all->pencil);
	return (0);
}

int	one_philo(t_all *all)
{
	printf("%-7d : philo 1  is thinking\n", 0);
	printf("%-7d : philo 1  take a fork\n", 0);
	usleep(all->death_time * 1000);
	printf("%-7d : philo 1  is dead\n", all->death_time);
	return (0);
}
