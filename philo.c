/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:45:48 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/19 14:38:52 by mstiedl          ###   ########.fr       */
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
	}
	else
		write(2, "Incorrect input", 15);
	free_list(listfirst(threads), 0);
	return (0);
}

void	philo_init(t_philo *philos, char **av)
{
	philos->total = ft_atoi(av[1]);
	philos->die = ft_atoi(av[2]);
	philos->eat = ft_atoi(av[3]);
	philos->sleep = ft_atoi(av[4]);
	philos->exit = 0;
	gettimeofday(&philos->start, NULL);
}

int time_keep(t_list *phil, int q)
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
		if (phil->data->exit == 1)
			return (-1);
		if (get_time(phil, 0) >= phil->data->die)
			return (-1);
	}
	return (0);
}

int	get_time(t_list *p, int arg)
{
	if (arg == 0)
		return((p->data->l_meal.tv_sec * 1000)\
		 + (p->data->l_meal.tv_usec / 1000));
	else if (arg == 1)
	{
		return (((p->data->l_meal.tv_sec - p->data->start.tv_sec) * 1000)\
		+ ((p->data->l_meal.tv_usec - p->data->start.tv_usec) / 1000));	
	}
	return (-1);
}
