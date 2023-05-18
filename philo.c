/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:45:48 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/18 21:05:48 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_list		*threads;
	t_params	params;
	int			len;

	len = -1;
	threads = NULL;
	if (ac == 5 || ac == 6)
	{
		params = get_params(av, ac);
		make_list(params, &threads);
		while (++len < params.total)
		{
			pthread_join(threads->data->thread_id, NULL);
			threads = threads->next;
		}
		free_list(threads, 0);
	}
	else
		error("Incorrect input");
	return (0);
}

t_params	get_params(char ** av, int ac)
{
	t_params	params;
	
	params.total = parse_arg(av[1], 0);
	params.die = parse_arg(av[2], 0);
	params.eat = parse_arg(av[3], 0);
	params.sleep = parse_arg(av[4], 0);
	if (ac == 6)
		params.revs = parse_arg(av[5], 1);
	else
		params.revs = 0;
	return (params);
}

int	parse_arg(char *arg, int flag)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= 48 && arg[i] <= 57)
			i++;
		else
			error("Invalid argument");
	}
	i = ft_atoi(arg);
	if (i < 0)
		error("Invalid argument");
	if (flag && i == 0)
		error("Really? how is this supposed to work?");
	return (i);
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
	philos->eating = 0;
	philos->counter = 0;
	pthread_mutex_init(&philos->fork, NULL);
	return (philos);
}

int time_keep(t_list *phil, int q)
{
	struct timeval	start;
	struct timeval	pres;
	long			laps;
	
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&pres, NULL);
		laps = (((pres.tv_sec - start.tv_sec) * 1000)\
		+ ((pres.tv_usec - start.tv_usec) / 1000));
		// printf("TIME: %ld, %i\n", laps, q);
		if (laps == q)
			return (1);
		if (phil->data->exit == 1)
			return (-1);
		// if (arg == 1 && get_time(phil, 0) >= phil->data->d.die)
		// 	return (-1);
	}
	return (0);
}

int	get_time(t_list *p, int arg)
{
	struct timeval	pres;
	
	gettimeofday(&pres, NULL);
	if (arg == 0)
	{
		// return((p->data->l_meal.tv_sec * 1000)
		// + (p->data->l_meal.tv_usec / 1000));
		return (((pres.tv_sec - p->data->l_meal.tv_sec) * 1000)\
		+ ((pres.tv_usec - p->data->l_meal.tv_usec) / 1000));	// better this way
	}
	else if (arg == 1)
	{
		return (((pres.tv_sec - p->start.tv_sec) * 1000)\
		+ ((pres.tv_usec - p->start.tv_usec) / 1000));	
	}
	return (-1);
}
