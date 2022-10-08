/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:33:08 by hrolle            #+#    #+#             */
/*   Updated: 2022/10/08 22:33:09 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac > 6)
		return (handle_error("trop d'argments", NULL, NULL));
	while (av[i])
	{
		if (av[i][0] == '0')
			return (handle_error("argment(s) invalide", NULL, NULL));
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (handle_error("argment(s) invalide", NULL, NULL));
			j++;
		}
		i++;
	}
	return (0);
}

void	set_all(t_all *all, int ac, char **av)
{
	all->philos = ft_atoui(av[1]);
	all->death = 0;
	all->death_time = ft_atoui(av[2]);
	all->eat_time = ft_atoui(av[3]);
	all->sleep_time = ft_atoui(av[4]);
	if (ac == 6)
		all->each_eat_time = ft_atoui(av[5]) + 1;
	else
		all->each_eat_time = 0;
}

t_philo	*set_philo(t_all *all)
{
	unsigned int	i;
	t_philo			*ret;

	i = 0;
	ret = malloc(all->philos * sizeof(t_philo));
	if (!ret)
		return (NULL);
	while (i < all->philos)
	{
		ret[i].each_eat_time = all->each_eat_time;
		ret[i].all = all;
		ret[i].n_philo = i + 1;
		ret[i].is_dead = my_time();
		i++;
	}
	return (ret);
}

int	set_mutex(t_all *all)
{
	unsigned int	i;

	i = 0;
	all->mufork = malloc(all->philos * sizeof(pthread_mutex_t));
	if (!all->mufork)
		return (1);
	while (i < all->philos)
		pthread_mutex_init(&all->mufork[i++], NULL);
	pthread_mutex_init(&all->pencil, NULL);
	return (0);
}
