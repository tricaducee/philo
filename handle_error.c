/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:32:04 by hrolle            #+#    #+#             */
/*   Updated: 2022/10/08 22:32:06 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mufork(t_all *all)
{
	unsigned int	i;

	i = 0;
	while (i < all->philos)
		pthread_mutex_destroy(&all->mufork[i++]);
	pthread_mutex_destroy(&all->pencil);
}

int	handle_error(char *str, t_all *all, t_philo *philos)
{
	if (all && all->mufork)
	{
		destroy_mufork(all);
		free(all->mufork);
	}
	if (philos)
		free(philos);
	printf("Error: %s\n", str);
	return (1);
}
