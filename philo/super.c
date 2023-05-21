/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:47:03 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/21 17:33:01 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*superviser(void *philosophers)
{
	t_list *philos;
	
	philos = (t_list *)philosophers;
	while(philos)
	{
		if (get_time(philos, 0) > philos->data->d->die)
		{
			if (end(philos, 0) == -1)
				return (0);
		}
		philos = philos->next;
		usleep(50);
	}
	return (0);
}

int	death_check(t_list *phil, int arg)
{
	pthread_mutex_lock(&phil->data->exit_m);
	if (phil->data->exit == 1)
	{
		if (arg == 1)
		{
			pthread_mutex_unlock(&phil->data->fork);
			pthread_mutex_unlock(&phil->next->data->fork);
			pthread_mutex_unlock(&phil->data->exit_m);
			return (-1);
		}
		else if (arg == 2)
		{
			pthread_mutex_unlock(&phil->data->fork);
			pthread_mutex_unlock(&phil->data->exit_m);
			return (-1);
		}
	}
	pthread_mutex_unlock(&phil->data->exit_m);
	return (0);
}

int	printing(t_list *phil, int arg, char *act)
{
	int	time;
	
	pthread_mutex_lock(&phil->data->print);
	if (death_check(phil, 1) == -1)
			return (-1);
	// maybe need a mutex lock here to check exit status
	time = get_time(phil, 1);
	if (arg == 1)
	{
		printf("%i ms: Philosopher %i has taken a fork%i\n", \
			time, phil->name, phil->name);
		printf("%i ms: Philosopher %i has taken a fork%i\n", \
			time, phil->name, phil->next->name);
		printf("%i ms: Philosopher %i is %s\n", time, phil->name, act);
	}
	else if (arg == 2)
		printf("%i ms: Philosopher %i is %s\n", time, phil->name, act);
	else if (arg == 3)
		printf("%i ms: Philosopher %i DIED\n", time, phil->name);
	else if (arg == 4)
		printf("%i ms: All Philosophers have eaten at least %i times\n", \
			time, phil->data->d->revs);
	pthread_mutex_unlock(&phil->data->print);
	return (0);
}