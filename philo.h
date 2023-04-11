/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:46:05 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/11 14:02:52 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct	s_philosopher
{
	int				die;
	int				eat;
	int				sleep;
	int				total;
	struct timeval	start;
	struct timeval	l_meal;
	pthread_t		thread_id;
	pthread_mutex_t	forks;
}				t_philo;

typedef struct	s_list
{
	int		name;
	t_philo	*data;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

void	*func_philo(void *info);
int		time_keep(int q);
void	philo_init(t_philo *philos, char **av);
//tool
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
//list_funcs
void	make_list(t_philo *data, t_list **head);
void	free_list(t_list *lst, int error);
void	ft_listadd_back(t_list **lst, t_list *new);

#endif