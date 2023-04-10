/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:45:48 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/10 15:32:32 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	struct timeval	start;
	t_philo			philos;
	// pthread_t		*thread;
	int				i;

	philo_init(&philos, av);
	// thread = ft_calloc(philos.total, sizeof(pthread_t)); //protection!?
	i = 0;
	if (ac == 5)
	{
		gettimeofday(&start, NULL);
		while (i++ < philos.total)
			pthread_create(&philos.id[i], NULL, func_philo, &philos);
	}
	else
		write(2, "Incorrect input", 15);
}

void	func_philo(void *info)
{
	struct timeval to_die;
	t_philo philo;
	
	philo = (t_philo *)info;
	gettimeofday(&to_die, NULL);
	while ((to_die.tv_sec * 1000 + to_die.tv_usec / 1000) < philo.die)
	{
		if (check_forks() == 0)
			eating();
		else
			sleeping(); // use usleep function - suspends thread for x microsecs	
	}
	
}

int time_keep(int q)
{
	struct timeval	start;
	struct timeval	pres;
	double			laps;
	
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&pres, NULL);
		laps = (((pres.tv_sec - start.tv_sec) * 1000)\
		+ ((pres.tv_usec - start.tv_usec) / 1000));
		if (laps == q)
			return (1);
	}
	return (0);
}

void	philo_init(t_philo *philos, char **av)
{
	philos->total = ft_atoi(av[1]);
	philos->die = ft_atoi(av[2]);
	philos->eat = ft_atoi(av[3]);
	philos->sleep = ft_atoi(av[4]);
}