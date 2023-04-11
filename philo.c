/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:45:48 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/11 15:51:00 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		philos;
	t_list		*threads;

	threads = NULL;
	if (ac == 5)
	{
		philo_init(&philos, av);
		make_list(&philos, &threads);
		while (threads->next)
		{
			pthread_join(threads->data->thread_id, NULL);
			threads = threads->next;
		}
		// 	pthread_create(thread, NULL, func_philo, (void*)&philos);
	}
	else
		write(2, "Incorrect input", 15);
	return (0);
}

void	*func_philo(void *info)
{
	int	time_dif;
	t_list philos;
	
	philos = *(t_list *)info;
	gettimeofday(&philos.data->l_meal, NULL);
	time_dif = (((philos.data->l_meal.tv_sec - philos.data->start.tv_sec) * 1000) + ((philos.data->l_meal.tv_usec - philos.data->start.tv_usec) / 1000));
	printf("At %i ms philosopher %i was born\n", time_dif, philos.name);
	while (get_time(philos) < philos.data->die)
	{
		if (check_last_meal(philos) == 0)
			eating();
		else
			sleeping(); // use usleep function - suspends thread for x microsecs	
	}
	return (0);
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
	gettimeofday(&philos->start, NULL);
}

int	check_last_meal(t_list 	philos)
{
	if (philos.name == 1 || philos)
	if (get_time(philos) >= get_time(philo->next)\
	&& get_time(philos) >= get_time(philo->prev))
		return(check_forks())
	return (-1);
}

int	get_time(t_list p)
{
	return((p.data->l_meal.tv_sec * 1000) + (p.data->l_meal.tv_usec / 1000));
}