/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:18:00 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/11/19 20:51:31 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	destroy_mutex(t_phil *phil, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (pthread_mutex_destroy(phil->room->mutexfork + i) != 0)
			return (0);
	}
	if (pthread_mutex_destroy(phil->room->mutexdeath) != 0)
		return (0);
	if (pthread_mutex_destroy(phil->room->mutexprint) != 0)
		return (0);
	if (pthread_mutex_destroy(phil->room->mutexlastmeal) != 0)
		return (0);
	return (1);
}

int	destroy(t_phil *phil, pthread_t *threads, int len)
{
	int	i;

	i = -1;
	if (phil->room->number_of_philosophers != 1)
	{
		while (++i < len)
		{
			if (pthread_join(threads[i], NULL) != 0)
				return (ERROR);
		}
	}
	else
	{
		if (pthread_join(threads[0], NULL) != 0)
			return (ERROR);
	}
	if (!destroy_mutex(phil, len))
		return (free_room(phil->room), free_phil(phil), ERROR);
	free_room(phil->room);
	free_phil(phil);
	return (0);
}
