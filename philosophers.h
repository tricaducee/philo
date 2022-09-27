#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct S_all
{
	pthread_mutex_t		*mufork;
	unsigned int		philos;
	unsigned long		start_time;	
	unsigned int		death;
	unsigned int		death_time;
	unsigned int		eat_time;
	unsigned int		sleep_time;
	unsigned int		think_time;
	unsigned int		each_eat_time;
}						t_all;

typedef	struct	S_philo
{
	t_all 			*all;
	pthread_t		philo_id;
	unsigned int	each_eat_time;
	unsigned int	n_philo;
}					t_philo;

void				handle_error(char *str);
t_philo				*set_philo(t_all *all);
void				set_all(t_all *all, int ac, char **av);
unsigned			ft_atoui(char *s);
void				*philo_func(void *philo);
unsigned long		my_time(void);
//void	philo(t_all *all, unsigned i);

#endif