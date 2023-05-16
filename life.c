/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:57:08 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/16 21:30:13 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func_philo(void *info)
{
	t_list *philos;
	
	philos = (t_list *)info;
	// printf("HERE: %i\n", philos->name);
	while (1) // maybe wont need this
	{
		// printf("TIME:%i, DIE:%i\n", get_time(philos, 0), philos->data->d.die);
		if (grab_fork(philos, philos->next) == 0)
			eating(philos);
		// else
		// 	thinking(philos);
		if (philos->data->exit == 1)
		{
			pthread_mutex_destroy(&philos->data->fork);
			return (0); // use usleep function - suspends thread for x microsecs	
		}
	} // in thinking check if time to die has past coz then he's dead
	// dead(philos);
	return(0);
}

// int	check_forks(t_list *philos)
// {
//     t_list  *first;
//     // t_list  *last;

//     // first = listfirst(philos);
//     // last = listlast(philos);
// 	// if (philos->name == 1)
// 	// 	return(grab_fork(philos, philos->next));
// 	if (philos->name == philos->data->d.total)
// 		return(grab_fork(philos, first));
// 	else
// 		return(grab_fork(philos, philos->next));	
// 	return (-1);
// }

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
	phil->data->eating = 1;
	time_keep(phil, phil->data->d.eat);
	pthread_mutex_unlock(&phil->data->fork);
	// if (phil->name == phil->data->d.total)
		// pthread_mutex_unlock(&phil->data->fork);
	// else
	pthread_mutex_unlock(&phil->next->data->fork);
	gettimeofday(&phil->data->l_meal, NULL);
	printf("%i ms: Philosopher %i is sleeping\n", get_time(phil, 1), phil->name);
	phil->data->eating = 0;
	time_keep(phil, phil->data->d.sleep);
	printf("%i ms: Philosopher %i is thinking\n", get_time(phil, 1), phil->name);
	thinking(phil);
}

void	thinking(t_list *phil) // i fucked up! there is no set thinking time 
{
	printf("%i ms: Philosopher %i is thinking\n", get_time(phil, 1), phil->name);
	// if (time_keep(phil, phil->data->eat) == -1)
		// return ;
}

void	dead(t_list *phil)
{
	t_list *temp;
	int		len;

	len = phil->data->d.total;	
	printf("%i ms: Philosopher %i DIED\n", get_time(phil, 1), phil->name);
	temp = phil;
	// start = listfirst(phil);
	while(len--)
	{
		temp->data->exit = 1;
		temp = temp->next;
	}
	pthread_mutex_destroy(&phil->data->fork);
	exit(1);
}

int	death_check(t_list *phil)
{
	t_list *temp;
	int		len;
	
	len = phil->data->d.total;
	temp = phil;
	// first = listfirst(phil);
	while(len--)
	{
		// printf("HERE: name %i\n", temp->name);
		if (temp->data->eating == 0 && get_time(temp, 0) > temp->data->d.die)
		{
			printf("HERE: dead %i\n", temp->name);
			dead(temp);
		}
		temp = temp->next;
	}
	return (1);
}
