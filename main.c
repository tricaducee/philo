/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:32:17 by hrolle            #+#    #+#             */
/*   Updated: 2022/10/09 17:53:02 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	print_struct(t_all *all)
// {
// 	printf("\nall struct :\nphilos = %u\ndeath = %u\ndeath_time =
//		%u\neat_time = %u\nsleep_time = %u\n", all->philos, all->death,
//		all->death_time, all->eat_time, all->sleep_time);
// }

void	clean(t_all *all, t_philo *philos)
{
	destroy_mufork(all);
	free(philos);
	free(all->mufork);
}

unsigned int	ft_atoui(char *s)
{
	unsigned int	n;

	n = 0;
	while (*s == '\t' || *s == '\n' || *s == '\v'
		|| *s == '\f' || *s == '\r' || *s == ' ')
		s++;
	while (*s <= '9' && *s >= '0')
	{
		n *= 10;
		n += *s - 48;
		s++;
	}
	return (n);
}

void	pair(t_all *all, t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < all->philos)
	{
		if (!(i % 2))
			pthread_create(&philos[i].philo_id, NULL, philo_func, &philos[i]);
		i++;
	}
}

void	odd(t_all *all, t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < all->philos)
	{
		if (i % 2)
			pthread_create(&philos[i].philo_id, NULL, philo_func, &philos[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_all			all;
	t_philo			*philos;
	unsigned int	i;

	if (ac < 5)
		return (handle_error("pas assez d'argments", NULL, NULL));
	if (check_arg(ac, av))
		return (1);
	set_all(&all, ac, av);
	if (all.philos == 1)
		return (one_philo(&all));
	philos = set_philo(&all);
	if (!philos)
		return (handle_error("philos malloc echecs", NULL, NULL));
	if (set_mutex(&all))
		return (handle_error("philos malloc echecs", &all, philos));
	all.start_time = my_time();
	odd(&all, philos);
	usleep(500);
	pair(&all, philos);
	i = 0;
	while (i < all.philos)
		pthread_join(philos[i++].philo_id, NULL);
	clean(&all, philos);
	return (0);
}
