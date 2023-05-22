/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:47 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/22 17:43:42 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_list(t_params *params, t_list **head)
{
	long			i;
	t_list			*node;
	struct timeval	start;
	pthread_mutex_t	print;

	i = 0;
	pthread_mutex_init(&print, NULL);
	gettimeofday(&start, NULL);
	while (++i <= params->total)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return (-1);
		node->name = i;
		node->data = philo_init(params, i);
		node->data->print = &print;
		node->start = start;
		node->next = NULL;
		node->prev = NULL;
		ft_listadd_back(head, node);
	}
	(*head)->prev = listlast(*head);
	listlast(*head)->next = *head;
	create_threads(*head, i);
	return (0);
}

void	create_threads(t_list *philos, int i)
{
	pthread_t	super_id;

	while (--i)
	{	
		gettimeofday(&philos->data->l_meal, NULL);
		philos->data->super_id = &super_id;
		pthread_create(&philos->data->thread_id, NULL, func_philo, philos);
		usleep(10);
		philos = philos->next;
	}
	pthread_create(&super_id, NULL, superviser, philos);
	pthread_join(super_id, NULL);
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

t_list	*listlast(t_list *current)
{
	t_list	*temp;

	temp = current;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
