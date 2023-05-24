/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:47:03 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/24 10:40:25 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*superviser(void *philosophers)
{
	t_list	*philos;
	long	time;

	philos = (t_list *)philosophers;
	while (philos)
	{
		usleep(10);
		time = get_time(philos, 0);
		if (time > philos->data->d->die)
		{
			end(philos, 0);
			return (0);
		}
		if (philos->data->d->revs != 0)
			if (counter_check(philos) == 0)
				return (0);
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
		}
		pthread_mutex_unlock(&phil->data->exit_m);
		return (-1);
	}
	pthread_mutex_unlock(&phil->data->exit_m);
	return (0);
}

int	printing(t_list *phil, int arg, char *act)
{
	int	time;

	pthread_mutex_lock(phil->data->print);
	if (death_check(phil, arg) == -1)
	{
		pthread_mutex_unlock(phil->data->print);
		return (-1);
	}
	time = get_time(phil, 1);
	if (arg == 1)
	{
		printf("%i ms: Philosopher %i has taken a fork\n", \
			time, phil->name);
		printf("%i ms: Philosopher %i has taken a fork\n", \
			time, phil->name);
		printf("%i ms: Philosopher %i is %s\n", time, phil->name, act);
	}
	else if (arg == 2)
		printf("%i ms: Philosopher %i is %s\n", time, phil->name, act);
	pthread_mutex_unlock(phil->data->print);
	return (0);
}

void	end_print(t_list *phil, int arg)
{
	int	time;

	time = get_time(phil, 1);
	if (arg == 1)
		printf("%i ms: Philosopher %i DIED\n", time, phil->name);
	else if (arg == 2)
	{
		printf("%i ms: All Philosophers have eaten at least %li times\n", \
			time, phil->data->d->revs);
		pthread_mutex_lock(&phil->data->end_m);
		phil->data->flag_end = 1;
		pthread_mutex_unlock(&phil->data->end_m);
	}
}
