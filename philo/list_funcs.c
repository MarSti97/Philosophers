/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs->c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:47:31 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/19 17:38:04 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_list(t_params *params, t_list **head)
{
	long			i;
	t_list			*node;
	struct timeval	start;
	// pthread_mutex_t	print;

	i = 0;
	// pthread_mutex_init(&print, NULL);
	gettimeofday(&start, NULL);
	while (++i <= params->total)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return (-1);
		node->name = i;
		node->data = philo_init(params, i); // one by one like this
		// node->data->print = print;
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
	return (0);
}

void	create_threads(t_list *philos, int i)
{
	pthread_t	super_id;
	
	while(--i)
	{	
		gettimeofday(&philos->data->l_meal, NULL);
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
	long	len;

	len = lst->data->d->total;
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

t_list	*listlast(t_list *current)
{
	t_list	*temp;

	temp = current;
	while(temp->next)
		temp = temp->next;
	return (temp);
}
