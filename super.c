/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:47:03 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/19 18:52:20 by mstiedl          ###   ########.fr       */
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