/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:46:05 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/10 15:31:43 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct	s_philosopher
{
	int				die;
	int				eat;
	int				sleep;
	int				total;
	pthread_t		id[total]; // maybe??
	pthread_mutex_t	forks[total];
}				t_philo;

void	func_philo(void *info);
int		time_keep(int q);
void	philo_init(t_philo *philos, char **av);
//tool
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif