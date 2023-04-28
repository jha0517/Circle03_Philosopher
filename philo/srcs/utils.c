/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:38:53 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/02 17:37:57 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	ft_atoi_base2(long int i, const char *str)
{
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long int	i;
	long int	j;
	long int	sum;

	sum = 0;
	i = 0;
	j = 1;
	i = ft_atoi_base2(i, str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -j;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + str[i] - 48;
		if (j == 1 && sum > 2147483647)
			return (-1);
		if (j == -1 && sum > 2147483648)
			return (0);
		i++;
	}
	return (sum * j);
}

unsigned long	get_time(struct timeval start, struct timeval stop)
{
	return ((((stop.tv_sec - start.tv_sec) * 1000000 + \
				stop.tv_usec - start.tv_usec) / 100) / 10);
}

void	free_room(t_room *room)
{
	free(room->mutexdeath);
	free(room->mutexprint);
	free(room->mutexfork);
	free(room->mutexlastmeal);
	free(room);
}

void	free_phil(t_phil *phil)
{
	free(phil);
}
