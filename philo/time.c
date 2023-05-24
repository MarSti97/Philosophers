/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:03:44 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/24 10:20:36 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_keep(t_list *phil, long q)
{
	struct timeval	start;
	struct timeval	pres;
	long			laps;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(10);
		gettimeofday(&pres, NULL);
		laps = (((pres.tv_sec - start.tv_sec) * 1000) \
		+ ((pres.tv_usec - start.tv_usec) / 1000));
		if (laps >= q)
			break ;
		pthread_mutex_lock(&phil->data->exit_m);
		if (phil->data->exit == 1)
		{
			pthread_mutex_unlock(&phil->data->exit_m);
			return (-1);
		}
		pthread_mutex_unlock(&phil->data->exit_m);
	}
	return (0);
}

long	get_time(t_list *p, int arg)
{
	struct timeval	pres;

	gettimeofday(&pres, NULL);
	if (arg == 0)
	{
		return (((pres.tv_sec - p->data->l_meal.tv_sec) * 1000) \
		+ ((pres.tv_usec - p->data->l_meal.tv_usec) / 1000));
	}
	else if (arg == 1)
	{
		return (((pres.tv_sec - p->start.tv_sec) * 1000) \
		+ ((pres.tv_usec - p->start.tv_usec) / 1000));
	}
	return (-1);
}
