/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:46:05 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/27 11:38:38 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct	s_params
{
	int				die;
	int				eat;
	int				sleep;
	int				total;
}				t_params;

typedef struct	s_philosopher
{
	int				name; 
	int				exit;
	int				deadlock;
	int				eating;
	t_params		d;
	struct timeval	l_meal;
	pthread_t		thread_id;
	pthread_mutex_t	fork;
}				t_philo;

typedef struct	s_list
{
	int				name;
	t_philo			*data;
	struct timeval	start;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;


t_params	get_params(char ** av);
t_philo		*philo_init(t_params params, int name);
int			time_keep(t_list *phil, int q);
int			get_time(t_list *p, int arg);
//tool
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
void	error(char *msg);
//list_funcs
void	make_list(t_params params, t_list **head);
void	free_list(t_list *lst, int error);
void	ft_listadd_back(t_list **lst, t_list *new);
t_list	*listfirst(t_list *current);
t_list	*listlast(t_list *current);
// life
void	*func_philo(void *info);
int		check_forks(t_list *philos);
int		dying(t_list *left, t_list *phil, t_list *right);
int		grab_fork(t_list *right, t_list *left);
int		death_check(t_list *phil);
// int		time(t_list *p);
void	eating(t_list *phil);
void	thinking(t_list *phil);
void	dead(t_list *phil);

// fork1 p1 fork2 p2 fork3 p3 fork4 p4 fork5 p5

#endif