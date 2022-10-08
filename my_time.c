/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:32:28 by hrolle            #+#    #+#             */
/*   Updated: 2022/10/08 22:32:30 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	my_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}
