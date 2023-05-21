/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:17:36 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/21 17:03:49 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	res;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (nptr[i] <= 57 && nptr[i] >= 48)
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (res * neg);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
	{
		return (0);
	}
	while (i < nmemb * size)
	{
		((unsigned char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}

int	error(char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		write(2, &msg[i], 1);
	return (-1);
}
