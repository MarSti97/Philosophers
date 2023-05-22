/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:57:08 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/22 18:05:57 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func_philo(void *info)
{
	t_list	*philos;

	philos = (t_list *)info;
	// printf("HERE:name %i, time %i\n", philos->name, get_time(philos, 1));
	if (philos->data->d->total == 1)
	{
		printf("These is only one fork on the table, Philosopher 1 can't eat\n");
		return (0);
	}
	while (1)
	{
		if (grab_fork(philos, philos->next) == -1)
			return (0);
		if (eating(philos) == -1)
			return (0);
	}
	return (0);
}

int	grab_fork(t_list *right, t_list *left)
{
	if (right->name % 2 == 0)
	{
		pthread_mutex_lock(&right->data->fork);
		// if (death_check(right, 0) == -1)
		// 	return (-1);
		pthread_mutex_lock(&left->data->fork);
		if (printing(right, 1, "eating") == -1)
			return (-1);
	}
	else
	{
		pthread_mutex_lock(&left->data->fork);
		// if (death_check(left, 0) == -1)
		// 	return (-1);
		pthread_mutex_lock(&right->data->fork);
		if (printing(right, 1, "eating") == -1)
			return (-1);
	}
	return (0);
}

int	eating(t_list *phil)
{
	int	dead;

	dead = 0;
	gettimeofday(&phil->data->l_meal, NULL);
	dead = time_keep(phil, phil->data->d->eat);
	pthread_mutex_unlock(&phil->data->fork);
	pthread_mutex_unlock(&phil->next->data->fork);
	if (dead == -1)
		return (-1);
	if (phil->data->d->revs != 0)
		if (counter_check(phil) == -1)
			return (-1);
	if (printing(phil, 2, "sleeping") == -1)
		return (-1);
	if (time_keep(phil, phil->data->d->sleep) == -1)
		return (-1);
	if (printing(phil, 2, "thinking") == -1)
		return (-1);
	return (0);
}

int	end(t_list *phil, int arg)
{
	t_list	*temp;
	long	len;

	len = phil->data->d->total;
	temp = phil;
	while (len--)
	{
		pthread_mutex_lock(&temp->data->exit_m);
		temp->data->exit = 1;
		pthread_mutex_unlock(&temp->data->exit_m);
		temp = temp->next;
	}
	if (arg == 0)
		end_print(phil, 1);
	else if (arg == 1)
		end_print(phil, 2);
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
