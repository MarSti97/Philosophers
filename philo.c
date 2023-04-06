/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:45:48 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/06 18:07:21 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	pthread_t	p;
	int	philos;
	int i;

	philos = ft_atoi(av[1]);
	i = 0;
	if (ac == 5)
	{
		while (i++ < philos)
			pthread_create(&p, NULL, func_philo);
	}
	else
		write(2, "Incorrect input", 15);
}

void	func_philo(void *)
{
	
}