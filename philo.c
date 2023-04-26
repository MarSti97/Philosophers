/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:45:48 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/26 19:51:42 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_list		*threads;
	t_params	params;

	threads = NULL;
	if (ac == 5)
	{
		params = get_params(av);
		make_list(params, &threads);
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

t_params	get_params(char ** av)
{
	t_params	params;
	
	params.total = ft_atoi(av[1]);
	params.die = ft_atoi(av[2]);
	params.eat = ft_atoi(av[3]);
	params.sleep = ft_atoi(av[4]);
	return (params);
}

t_philo	*philo_init(t_params params, int name)
{
	t_philo *philos;

	philos = malloc(sizeof(t_philo));
	if (!philos)
		return (NULL); // add error message and quit
	philos->name = name;
	if (philos->name % 2 == 0)
		philos->deadlock = 0;
	else
		philos->deadlock = 1;
	philos->d = params;
	philos->exit = 0;
	pthread_mutex_init(&philos->fork, NULL);
	return (philos);
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
		if (get_time(phil, 0) >= phil->data->d.die)
			return (-1);
	}
	return (0);
}

int	get_time(t_list *p, int arg)
{
	struct timeval	pres;
	
	gettimeofday(&pres, NULL);
	if (arg == 0)
		return((p->data->l_meal.tv_sec * 1000)\
		 + (p->data->l_meal.tv_usec / 1000));
	else if (arg == 1)
	{
		return (((pres.tv_sec - p->start.tv_sec) * 1000)\
		+ ((pres.tv_usec - p->start.tv_usec) / 1000));	
	}
	return (-1);
}
