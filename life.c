/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:57:08 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/19 19:07:49 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func_philo(void *info)
{
	t_list *philos;
	
	philos = (t_list *)info;
	while (1)
	{
		if (grab_fork(philos, philos->next) == -1)
			return (0);
		if (eating(philos) == -1)
			return (0);
	}
	return(0);
}

int grab_fork(t_list *right, t_list *left)

{
	if (right->name % 2 == 0)
	{
		pthread_mutex_lock(&right->data->fork);
		if (death_check(right, 2) == -1)
			return (-1);
		pthread_mutex_lock(&left->data->fork);
		if (death_check(right, 1) == -1)
			return (-1);
		usleep(10);
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, left->name);		
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, right->name);
	}
	else 
	{
		pthread_mutex_lock(&left->data->fork);
		if (death_check(left, 2) == -1)
			return (-1);
		pthread_mutex_lock(&right->data->fork);
		if (death_check(right, 1) == -1)
			return (-1);
		usleep(10);
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, right->name);
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, left->name);	
	}
	return (0);
}

int	eating(t_list *phil)
{
	int	dead;

	dead = 0;
	printf("%i ms: Philosopher %i is eating\n", get_time(phil, 1), phil->name);
	gettimeofday(&phil->data->l_meal, NULL);
	dead = time_keep(phil, phil->data->d->eat);
	pthread_mutex_unlock(&phil->data->fork);
	pthread_mutex_unlock(&phil->next->data->fork);
	if (phil->data->d->revs != 0)
		if (counter_check(phil) == -1)
			return (-1);
	if (dead == -1)
		return (-1);
	printf("%i ms: Philosopher %i is sleeping\n", get_time(phil, 1), phil->name);
	if (time_keep(phil, phil->data->d->sleep) == -1)
		return (-1);
	printf("%i ms: Philosopher %i is thinking\n", get_time(phil, 1), phil->name);
	return (0);
}

int	end(t_list *phil, int arg)
{
	t_list	*temp;
	long	len;

	len = phil->data->d->total;
	if (arg == 0)
		printf("%i ms: Philosopher %i DIED\n", get_time(phil, 1), phil->name);
	else if (arg == 1)
		printf("%i ms: All Philosophers have eaten at least %li times\n", get_time(phil, 1), phil->data->d->revs);
	temp = phil;
	while (len--)
	{
		pthread_mutex_lock(&temp->data->exit_m);
		temp->data->exit = 1;
		pthread_mutex_unlock(&temp->data->exit_m);
		usleep(10);
		temp = temp->next;
	}
	return (-1);
}

int	counter_check(t_list *philos)
{
	t_list	*temp;
	long	len;

	pthread_mutex_lock(&philos->data->counter_m);
	philos->data->counter++;
	pthread_mutex_unlock(&philos->data->counter_m);
	len = philos->data->d->total;
	temp = philos;
	while (len--)
	{
		pthread_mutex_lock(&temp->data->counter_m);
		if (temp->data->counter >= temp->data->d->revs)
			temp = temp->next;
		else
		{
			pthread_mutex_unlock(&temp->data->counter_m);
			return (0);
		}
		pthread_mutex_unlock(&temp->prev->data->counter_m);
	}
	return (end(philos, 1));
}
