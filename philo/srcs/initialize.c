/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:12:32 by hyujung           #+#    #+#             */
/*   Updated: 2022/12/02 17:38:13 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

pthread_mutex_t	*ft_malloc_memset(int size)
{
	pthread_mutex_t	*result;

	result = (pthread_mutex_t *) malloc(size);
	if (!result)
		return (NULL);
	memset(result, 0, size);
	return (result);
}

t_room	*add_mutex(t_room *room)
{
	int				num;

	if (!room)
		return (NULL);
	num = room->number_of_philosophers;
	room->mutexprint = ft_malloc_memset(sizeof(pthread_mutex_t));
	if (!room->mutexprint)
		return (free(room), NULL);
	room->mutexdeath = ft_malloc_memset(sizeof(pthread_mutex_t));
	if (!room->mutexdeath)
		return (free(room), free(room->mutexprint), NULL);
	room->mutexlastmeal = ft_malloc_memset(sizeof(pthread_mutex_t));
	if (!room->mutexlastmeal)
		return (free(room), free(room->mutexprint), \
		free(room->mutexdeath), NULL);
	room->mutexfork = ft_malloc_memset(sizeof(pthread_mutex_t) * num);
	if (!room->mutexfork)
		return (free(room), free(room->mutexprint), \
		free(room->mutexdeath), free(room->mutexlastmeal), NULL);
	return (room);
}

t_room	*create_room(int ac, char **av)
{
	t_room			*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	memset(room, 0, sizeof(t_room));
	room->number_of_philosophers = ft_atoi(av[1]);
	room->time_to_die = ft_atoi(av[2]);
	room->time_to_eat = ft_atoi(av[3]);
	room->time_to_sleep = ft_atoi(av[4]);
	room->loop = 1;
	room->all_ate = 0;
	room->total_number_of_times_eaten = 0;
	if (ac == 6)
		room->must_eat = ft_atoi(av[5]);
	else
		room->must_eat = -1;
	if (room->number_of_philosophers % 2 == 0)
		room->time_to_think = -1;
	else
		room->time_to_think = room->time_to_eat;
	return (room);
}

t_phil	*create_philosophers(t_room *room)
{
	t_phil			*phil;
	int				total;
	int				i;

	total = room->number_of_philosophers;
	phil = (t_phil *)malloc(sizeof(t_phil) * total);
	if (!phil)
		return (NULL);
	memset(phil, 0, sizeof(t_phil) * total);
	i = -1;
	while (++i < total)
	{
		phil[i].id = i;
		phil[i].number_of_times_eaten = 0;
		phil[i].room = room;
		phil[i].last_meal = 0;
	}
	return (phil);
}

t_phil	*init(int ac, char **av)
{
	t_phil			*phil;
	t_room			*room;

	room = create_room(ac, av);
	room = add_mutex(room);
	if (!room)
		return (NULL);
	phil = create_philosophers(room);
	if (!phil)
		return (free_room(room), NULL);
	return (phil);
}
