#include "philosophers.h"


void		print_struct(t_all *all)
{
	printf("\nall struct :\nphilos = %u\ndeath = %u\ndeath_time = %u\neat_time = %u\nsleep_time = %u\nthink_time = %u\n", all->philos, all->death, all->death_time, all->eat_time, all->sleep_time, all->think_time);
}

unsigned	ft_atoui(char *s)
{
	unsigned    n;

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

void	set_all(t_all *all, int ac, char **av)
{
	all->philos = ft_atoui(av[1]);
	//all->start_time = 0;
	all->death = 0;
	all->death_time = ft_atoui(av[2]);
	all->eat_time = ft_atoui(av[3]);
	all->sleep_time = ft_atoui(av[4]);
	all->think_time = all->death_time - all->sleep_time;
	if (ac == 6)
		all->each_eat_time = ft_atoui(av[5]) + 1;
	else
		all->each_eat_time = 0;
	print_struct(all);
}

t_philo	*set_philo(t_all *all)
{
	unsigned int	i;
	t_philo		*ret;

	i = 0;
	ret = malloc(all->philos * sizeof(t_philo));
	if (!ret)
		handle_error("echec malloc\n");
	while (i < all->philos)
	{
		ret[i].each_eat_time = 0;
		ret[i].all = all;
		ret[i].n_philo = i + 1;
		ret[i].is_dead = my_time();
		i++;
	}
	return (ret);
}
// set philos, on va faire un malloc de all->philo * sizeof(t_philo) puis remplir

void	set_mutex(t_all *all)
{
	unsigned int	i;

	i = 0;
	all->mufork = malloc(all->philos * sizeof(pthread_mutex_t));
	if (!all->mufork)
		handle_error("malloc foireux du mutexage");
	while (i < all->philos)
		pthread_mutex_init(&all->mufork[i++], NULL);
	pthread_mutex_init(&all->pencil, NULL);
}

void	pair(t_all *all, t_philo *philos)
{
	unsigned	i;

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
	unsigned	i;

	i = 0;
	while (i < all->philos)
	{
		if (i % 2)
			pthread_create(&philos[i].philo_id, NULL, philo_func, &philos[i]);
		i++;
	}
}

int main(int ac, char **av)
{
	t_all   		all;
	t_philo			*philos;
	unsigned int	i;

	if (ac < 5)
		handle_error("+ d'args");
	set_all(&all, ac, av);
	philos = set_philo(&all);
	set_mutex(&all);
	print_struct(&all);
	all.start_time = my_time();
	odd(&all, philos);
	usleep(5000);
	pair(&all, philos);
	i = 0;
	while (i < all.philos)
		pthread_join(philos[i++].philo_id, NULL);
	free(philos);
	free(all.mufork);
	print_struct(&all);
	return (0);
	// printf();
}