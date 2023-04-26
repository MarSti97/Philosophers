/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:57:08 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/26 19:36:20 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func_philo(void *info)
{
	t_list *philos;
	
	philos = (t_list *)info;
	// printf("HERE: %i\n", philos->name);
	gettimeofday(&philos->data->l_meal, NULL);
	while (get_time(philos, 0) < philos->data->d.die) // maybe wont need this
	{
		if (check_forks(philos) == 0)
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

int	check_forks(t_list *philos)
{
    t_list  *first;
    // t_list  *last;

    first = listfirst(philos);
    // last = listlast(philos);
	// if (philos->name == 1)
	// 	return(grab_fork(philos, philos->next));
	if (philos->name == philos->data->d.total)
		return(grab_fork(philos, first));
	else
		return(grab_fork(philos, philos->next));	
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
	if (right->name % 2 == 0)
	{
		pthread_mutex_lock(&right->data->fork);
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, right->name);
		pthread_mutex_lock(&left->data->fork);
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, left->name);		
	}
	else 
	{
		pthread_mutex_lock(&left->data->fork);
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, left->name);	
		pthread_mutex_lock(&right->data->fork);
		printf("%i ms: Philosopher %i has taken a fork%i\n", get_time(right, 1), right->name, right->name);
	}
	return (0);
}

void	eating(t_list *phil)
{
	printf("%i ms: Philosopher %i is eating\n", get_time(phil, 1), phil->name);
	if (time_keep(phil, phil->data->d.eat) == -1)
		return ;
	pthread_mutex_unlock(&phil->data->fork);
	if (phil->name == phil->data->d.total)
		pthread_mutex_unlock(&listfirst(phil)->data->fork);
	else
		pthread_mutex_unlock(&phil->next->data->fork);
	gettimeofday(&phil->data->l_meal, NULL);
	printf("%i ms: Philosopher %i is sleeping\n", get_time(phil, 1), phil->name);
	if (time_keep(phil, phil->data->d.sleep) == -1)
		return ;
	printf("%i ms: Philosopher %i is thinking\n", get_time(phil, 1), phil->name);
	// thinking(phil);
}

void	thinking(t_list *phil) // i fucked up! there is no set thinking time 
{
	printf("%i ms: Philosopher %i is thinking\n", get_time(phil, 1), phil->name);
	// if (time_keep(phil, phil->data->eat) == -1)
		// return ;
}

void	dead(t_list *phil)
{
	t_list *start;
	
	printf("%i ms: Philosopher %i DIED\n", get_time(phil, 1), phil->name);
	start = listfirst(phil);
	while(start->next)
	{
		start->data->exit = 1;
		start = start->next;
	}
	pthread_mutex_destroy(&phil->data->fork);
}