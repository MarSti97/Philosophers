/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:46:05 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/19 19:05:59 by mstiedl          ###   ########.fr       */
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
	long				die;
	long				eat;
	long				sleep;
	long				total;
	long				revs;
}				t_params;

typedef struct	s_philosopher
{
	int				name; 
	int				exit;
	int				deadlock;
	long			counter;
	t_params		*d;
	struct timeval	l_meal;
	pthread_t		thread_id;
	pthread_mutex_t	fork;
	pthread_mutex_t	exit_m;
	pthread_mutex_t	counter_m;
}				t_philo;

typedef struct	s_list
{
	int				name;
	t_philo			*data;
	struct timeval	start;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;


int			get_params(char ** av, int ac, t_params *params);
t_philo		*philo_init(t_params *params, int name);
int			time_keep(t_list *phil, long q);
int			get_time(t_list *p, int arg);
int			parse_arg(char *arg, int flag);
//tool
long		ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
int			error(char *msg);
//list_funcs
int			make_list(t_params *params, t_list **head);
void		free_list(t_list *lst, int error);
void		ft_listadd_back(t_list **lst, t_list *new);
t_list		*listlast(t_list *current);
void		create_threads(t_list *philos, int i);
// life
void		*func_philo(void *info);
int			grab_fork(t_list *right, t_list *left);
int			death_check(t_list *phil, int arg);
int			counter_check(t_list *philos);
void		*superviser(void *philosophers);
int			eating(t_list *phil);
int			end(t_list *phil, int arg);

#endif
