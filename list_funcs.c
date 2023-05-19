/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:47:31 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/19 16:48:41 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_list(t_params params, t_list **head)
{
	int		i;
	t_list	*node;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	while (++i <= params.total)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return ;
		node->name = i;
		node->data = philo_init(params, i); // one by one like this
		node->start = start;
		node->next = NULL;
		node->prev = NULL;
		gettimeofday(&node->data->l_meal, NULL);
		ft_listadd_back(head, node);
	}
	(*head)->prev = listlast(*head);
	listlast(*head)->next = *head;
	node = *head;
	create_threads(*head, i);
	// while(--i)
	// {	
	// 	pthread_create(&node->data->thread_id, NULL, func_philo, node);
	// 	usleep(100);
	// 	// printf("name: %i, deadlock: %i\n", node->name, node->data->deadlock);
	// 	node = node->next;
	// }
}

void	create_threads(t_list *philos, int i)
{
	// struct timeval	start;
	pthread_t	super_id;
	
	// gettimeofday(&start, NULL);
	while(--i)
	{	
		// philos->start = start;
		gettimeofday(&philos->data->l_meal, NULL);
		// printf("NAME: %i, time %i\n", philos->name, get_time(philos, 1));
		pthread_create(&philos->data->thread_id, NULL, func_philo, philos);
		usleep(50);
		philos = philos->next;
	}
	pthread_create(&super_id, NULL, superviser, philos);
	pthread_join(super_id, NULL);
}

void	free_list(t_list *lst, int error)
{
	t_list	*temp;
	int		len;

	len = lst->data->d.total;
	if (lst)
	{
		if (error == 1)
			write(2, "Error\n", 6);
		while (len--)
		{
			temp = lst;
			lst = lst->next;
			pthread_mutex_destroy(&temp->data->fork);
			pthread_mutex_destroy(&temp->data->exit_m);
			pthread_mutex_destroy(&temp->data->counter_m);
			free (temp->data);
			free (temp);
		}
	}
}

void	ft_listadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

// t_list	*listfirst(t_list *current)
// {
// 	t_list	*temp;

// 	temp = current;
// 	while(temp->prev)
// 		temp = temp->prev;
// 	return (temp);
// }

t_list	*listlast(t_list *current)
{
	t_list	*temp;

	temp = current;
	while(temp->next)
		temp = temp->next;
	return (temp);
}
