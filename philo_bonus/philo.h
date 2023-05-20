/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:46:05 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/20 20:42:25 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>


typedef struct	s_params
{
	int				die;
	int				eat;
	int				sleep;
	int				total;
	int				revs;
}				t_params;

typedef struct	s_philosopher
{
	int				name; 
	int				exit;
	int				deadlock;
	int				eating;
	int				counter;
	t_params		d;
	struct timeval	l_meal;
	pthread_t		thread_id;
	pthread_mutex_t	fork;
	pthread_mutex_t	print;
}				t_philo;

typedef struct	s_list
{
	int				name;
	t_philo			*data;
	struct timeval	start;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

t_params	get_params(char ** av, int ac);

#endif