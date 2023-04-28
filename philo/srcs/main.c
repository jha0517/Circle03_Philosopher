/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:17:45 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/04 18:25:01 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_time(t_phil *phil, int i, struct timeval now)
{
	int				t;

	if (pthread_mutex_lock(phil->room->mutexdeath) != 0)
		return (0);
	t = (get_time(phil->room->start, now) - phil[i].last_meal);
	if (pthread_mutex_unlock(phil->room->mutexdeath) != 0)
		return (0);
	if ((int)t > phil->room->time_to_die)
	{
		if (pthread_mutex_lock(phil->room->mutexdeath) != 0)
			return (0);
		phil->room->loop = 0;
		if (pthread_mutex_unlock(phil->room->mutexdeath) != 0)
			return (0);
		return (1);
	}
	return (0);
}

int	init_threads(t_phil *phil, pthread_t *threads)
{
	int				i;
	struct timeval	now;
	struct timeval	start;

	i = -1;
	gettimeofday(&start, NULL);
	phil[0].room->start = start;
	while (++i < phil->room->number_of_philosophers)
	{
		if (gettimeofday(&now, NULL) != 0)
			return (0);
		if (pthread_create(threads + i, NULL, philosopher, \
		(void *)(phil + i)) != 0)
			return (0);
	}
	return (2);
}

int	init_forks(t_phil *phil, int total)
{
	int	i;

	i = -1;
	while (++i < total)
	{
		if (pthread_mutex_init(phil->room->mutexfork + i, NULL) != 0)
			return (0);
	}
	return (1);
}

pthread_t	*start_threads(t_phil *phil)
{
	pthread_t		*threads;
	int				i;
	int				total;

	total = phil->room->number_of_philosophers;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * total);
	if (!threads)
		return (NULL);
	memset(threads, 0, sizeof(pthread_t) * total);
	if (!init_forks(phil, total))
		return (NULL);
	if (pthread_mutex_init(phil->room->mutexprint, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(phil->room->mutexdeath, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(phil->room->mutexlastmeal, NULL) != 0)
		return (NULL);
	i = init_threads(phil, threads);
	if (i == DIED_OR_ALL_ATE || !i)
		return (NULL);
	return (threads);
}

int	main(int ac, char **av)
{
	t_phil			*phil;
	pthread_t		*threads;

	if (check_arg(ac, av))
		return (0);
	if (ft_atoi(av[1]) == 0)
		return (printf("Please enter more than 0 philosopher.\n"), 0);
	phil = init(ac, av);
	if (!phil)
		return (ERROR);
	threads = start_threads(phil);
	if (!threads)
		return (free_room(phil->room), free_phil(phil), ERROR);
	checker(phil);
	destroy(phil, threads, ft_atoi(av[1]));
	free(threads);
	return (0);
}
