/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:57:08 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/19 14:42:59 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func_philo(void *info)
{
	t_list *philos;
	
	philos = (t_list *)info;
	pthread_mutex_init(&philos->data->fork, NULL);
	gettimeofday(&philos->data->l_meal, NULL);
	while (get_time(philos, 0) < philos->data->die) // maybe wont need this
	{
		if (check_last_meal(philos) == 0)
			eating(philos);
		else
			thinking(philos);
		if (philos->data->exit == 1)
		{
			pthread_mutex_destroy(&philos->data->fork);
			return (0); // use usleep function - suspends thread for x microsecs	
		}
	} // in thinking check if time to die has past coz then he's dead
	dead(philos);
	return(0);
}

int	check_last_meal(t_list *philos)
{
    t_list  *first;
    t_list  *last;

    first = listfirst(philos);
    last = listlast(philos);
	if (philos->name == 1)
	{
        if (dying(last, philos, philos->next) == 0) 
            return(grab_fork(philos, philos->next));
	}
	else if (philos->name == philos->data->total)
	{
		if (dying(philos->prev, philos, first) == 0)
            return(grab_fork(philos, first));
	}
	else
	{
        if (dying(philos->prev, philos, philos->next) == 0)
            return(grab_fork(philos, philos->next));	
	}
	return (-1);
}

int	dying(t_list *left, t_list *phil, t_list *right) // doing this might count as communication... might need to take it out
{
	int	time;

	time = get_time(phil, 0);
	if (time >= get_time(left, 0) && time >= get_time(right, 0))
		return (0);
	return (-1);
}

int grab_fork(t_list *right, t_list *left)
{
    if (pthread_mutex_lock(&right->data->fork) != 0)
		return (-2);
	printf("At %i ms: Philosopher %i has taken a fork", get_time(right, 1), right->name);
	if (pthread_mutex_lock(&left->data->fork) != 0)
		return (-3);
	printf("At %i ms: Philosopher %i has taken a fork", get_time(right, 1), right->name);
	return (0);
}

void	eating(t_list *phil)
{
	printf("At %i ms: Philosopher %i is eating", get_time(phil, 1), phil->name);
	if (time_keep(phil, phil->data->eat) == -1)
		return ;
	pthread_mutex_unlock(&phil->data->fork);
	if (phil->name == phil->data->total)
		pthread_mutex_unlock(&listfirst(phil)->data->fork);
	gettimeofday(&phil->data->l_meal, NULL);
	printf("At %i ms: Philosopher %i is sleeping", get_time(phil, 1), phil->name);
	if (time_keep(phil, phil->data->sleep) == -1)
		return ;
	thinking(phil);
}

void	thinking(t_list *phil)
{
	printf("At %i ms: Philosopher %i is thinking", get_time(phil, 1), phil->name);
	if (time_keep(phil, phil->data->eat) == -1)
		return ;
}

void	dead(t_list *phil)
{
	t_list *start;
	
	printf("At %i ms: Philosopher %i DIED", get_time(phil, 1), phil->name);
	start = listfirst(phil);
	while(start->next)
	{
		start->data->exit = 1;
		start = start->next;
	}
	pthread_mutex_destroy(&phil->data->fork);
}