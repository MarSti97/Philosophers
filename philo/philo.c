/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:45:48 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/23 16:21:52 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_list		*threads;
	t_params	*params;
	long		len;

	len = -1;
	threads = NULL;
	if (ac == 5 || ac == 6)
	{
		params = malloc(sizeof(t_params) * 1);
		if (get_params(av, ac, params) == -1)
			return (freedom(NULL, params));
		if (make_list(params, &threads) == -1)
			return (1);
		while (++len < params->total)
		{
			pthread_join(threads->data->thread_id, NULL);
			threads = threads->next;
		}
		freedom(&threads, params);
	}
	else
		error("Incorrect input");
	return (0);
}

int	get_params(char **av, int ac, t_params *params)
{
	if (parse_arg(av[1], 1) == -1)
		return (-1);
	params->total = ft_atol(av[1]);
	if (parse_arg(av[2], 0) == -1)
		return (-1);
	params->die = ft_atol(av[2]);
	if (parse_arg(av[3], 0) == -1)
		return (-1);
	params->eat = ft_atol(av[3]);
	if (parse_arg(av[4], 0) == -1)
		return (-1);
	params->sleep = ft_atol(av[4]);
	if (ac == 6)
	{	
		if (parse_arg(av[5], 1) == -1)
			return (-1);
		params->revs = ft_atol(av[5]);
	}
	else
		params->revs = 0;
	return (0);
}

int	parse_arg(char *arg, int flag)
{
	long	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= 48 && arg[i] <= 57)
			i++;
		else
			return (error("Invalid argument"));
	}
	i = ft_atol(arg);
	if (i < 0)
		return (error("Invalid argument"));
	if (flag && i == 0)
		return (error("Really? how is this supposed to work?"));
	return (0);
}

t_philo	*philo_init(t_params *params, int name)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * 1);
	if (!philos)
		return (NULL);
	philos->name = name;
	philos->d = params;
	philos->exit = 0;
	philos->counter = 0;
	philos->flag_end = 0;
	pthread_mutex_init(&philos->exit_m, NULL);
	pthread_mutex_init(&philos->counter_m, NULL);
	pthread_mutex_init(&philos->fork, NULL);
	pthread_mutex_init(&philos->end_m, NULL);
	return (philos);
}
