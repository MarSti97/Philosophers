/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:47:31 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/13 11:57:12 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_list(t_philo *data, t_list **head)
{
	int		i;
	t_list	*node;

	i = 0;
	while (++i <= data->total)
	{
		node = (t_list *)malloc(sizeof(t_list));
		if (!node)
			return ;
		node->name = i;
		// printf("name: %i\n", node->name);
		node->data = data;
		node->next = NULL;
		node->prev = NULL;
		ft_listadd_back(head, node);
		pthread_create(&node->data->thread_id, NULL, func_philo, (void *)node);
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