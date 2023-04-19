/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:46:05 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/19 14:37:02 by mstiedl          ###   ########.fr       */
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
	int				exit;
	struct timeval	start;
	struct timeval	l_meal;
	pthread_t		thread_id;
	pthread_mutex_t	fork;
}				t_philo;

typedef struct	s_list
{
	int		name;
	t_philo	*data;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

void	philo_init(t_philo *philos, char **av);
int		time_keep(t_list *phil, int q);
int		get_time(t_list *p, int arg);
//tool
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	error(char *msg);
//list_funcs
void	make_list(t_philo *data, t_list **head);
void	free_list(t_list *lst, int error);
void	ft_listadd_back(t_list **lst, t_list *new);
t_list	*listfirst(t_list *current);
t_list	*listlast(t_list *current);
// life
void	*func_philo(void *info);
int		check_last_meal(t_list *philos);
int		dying(t_list *left, t_list *phil, t_list *right);
int		grab_fork(t_list *right, t_list *left);
// int		time(t_list *p);
void	eating(t_list *phil);
void	thinking(t_list *phil);
void	dead(t_list *phil);

#endif