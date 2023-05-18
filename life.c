/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:57:08 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/18 15:41:41 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func_philo(void *info)
{
	t_list *philos;
	
	philos = (t_list *)info;
	while (1)
	{
		if (grab_fork(philos, philos->next) == 0)
			eating(philos);
		if (philos->data->d.revs != 0)
			counter_check(philos);
		if (philos->data->exit == 1)
		{
			pthread_mutex_destroy(&philos->data->fork);
			return (0); // use usleep function - suspends thread for x microsecs	
		}
	} // in thinking check if time to die has past coz then he's dead
	// dead(philos);
	return(0);
}

void	counter_check(t_list *philos)
{
    t_list  *temp;
	int		len;

	philos->data->counter++;
	len = philos->data->d.total;
	while (len--)
	{
		// printf("LEN: %i\n", len);
		if (temp->data->counter >= temp->data->d.revs)
			temp = temp->next;
		else
			return ;
	}
	end(philos, 1);
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
		pthread_mutex_lock(&left->data->fork);
		// usleep(100);
		printing(right, 1, NULL);
	}
	else 
	{
		pthread_mutex_lock(&left->data->fork);
		pthread_mutex_lock(&right->data->fork);
		// usleep(100);
		printing(right, 1, NULL);
	}
	return (0);
}

void	eating(t_list *phil)
{
	printing(phil, 2, "eating");
	gettimeofday(&phil->data->l_meal, NULL);
	phil->data->eating = 1;
	time_keep(phil, phil->data->d.eat);
	pthread_mutex_unlock(&phil->data->fork);
	pthread_mutex_unlock(&phil->next->data->fork);
	phil->data->eating = 0;
	printing(phil, 2, "sleeping");
	time_keep(phil, phil->data->d.sleep);
	printing(phil, 2, "thinking");
}

void	end(t_list *phil, int arg)
{
	t_list *temp;
	int		len;

	len = phil->data->d.total;
	if (arg == 0)
		printing(phil, 3, NULL);
	else if (arg == 1)
		printing(phil, 4, NULL);
	temp = phil;
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
	while(len--)
	{
		// printf("HERE: name %i\n", temp->name);
		if (get_time(temp, 0) > temp->data->d.die)
		{
			printf("HERE: dead %i\n", temp->name);
			end(temp, 0);
		}
		temp = temp->next;
	}
	return (1);
}

void	printing(t_list *phil, int arg, char *act)
{
	int	time;
	
	pthread_mutex_lock(&phil->data->print);
	time = get_time(phil, 1);
	if (arg == 1)
	{
		printf("%i ms: Philosopher %i has taken a fork%i\n", \
			time, phil->name, phil->name);
		printf("%i ms: Philosopher %i has taken a fork%i\n", \
			time, phil->name, phil->next->name);
	}
	else if (arg == 2)
		printf("%i ms: Philosopher %i is %s\n", time, phil->name, act);
	else if (arg == 3)
		printf("%i ms: Philosopher %i DIED\n", time, phil->name);
	else if (arg == 4)
		printf("%i ms: All Philosophers have eaten at least %i times\n", \
			time, phil->data->d.revs);
	pthread_mutex_unlock(&phil->data->print);
}
