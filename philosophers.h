/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:32:48 by hrolle            #+#    #+#             */
/*   Updated: 2022/10/08 22:32:50 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct S_all
{
	pthread_mutex_t		*mufork;
	pthread_mutex_t		pencil;
	unsigned int		philos;
	unsigned long		start_time;	
	unsigned int		death;
	unsigned int		death_time;
	unsigned int		eat_time;
	unsigned int		sleep_time;
	unsigned int		each_eat_time;
}						t_all;

typedef struct S_philo
{
	t_all			*all;
	pthread_t		philo_id;
	unsigned int	each_eat_time;
	unsigned int	n_philo;
	unsigned long	is_dead;
}					t_philo;

int					handle_error(char *str, t_all *all, t_philo *philos);
void				destroy_mufork(t_all *all);
int					check_arg(int ac, char **av);
t_philo				*set_philo(t_all *all);
void				set_all(t_all *all, int ac, char **av);
int					set_mutex(t_all *all);
unsigned int		ft_atoui(char *s);
void				*philo_func(void *philo);
unsigned long		my_time(void);
int					print_action(t_philo *philo, char *s, unsigned long time);
int					print_death(t_philo *philo, unsigned long time);
int					one_philo(t_all *all);

#endif
