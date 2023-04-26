/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:47:31 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/26 18:23:59 by mstiedl          ###   ########.fr       */
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
		ft_listadd_back(head, node);
	}
	node = *head;
	while(node)
	{	
		// printf("name: %i, deadlock: %i\n", node->name, node->data->deadlock);
		pthread_create(&node->data->thread_id, NULL, func_philo, node);
		node = node->next;
	}
}

void	free_list(t_list *lst, int error)
{
	t_list	*temp;

	if (lst)
	{
		if (error == 1)
			write(2, "Error\n", 6);
		while (lst != NULL)
		{
			temp = lst;
			lst = lst->next;
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

t_list	*listfirst(t_list *current)
{
	t_list	*temp;

	temp = current;
	while(temp->prev)
		temp = temp->prev;
	return (temp);
}

t_list	*listlast(t_list *current)
{
	t_list	*temp;

	temp = current;
	while(temp->next)
		temp = temp->next;
	return (temp);
}