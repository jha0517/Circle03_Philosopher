/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:46:15 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/04 18:22:38 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	debug_dead(t_phil *phil, unsigned long time)
{
	unsigned long	last_meal;

	pthread_mutex_lock(phil->room->mutexlastmeal);
	last_meal = phil->last_meal;
	pthread_mutex_unlock(phil->room->mutexlastmeal);
	printf("phil %i last meal was %lu. gotta \
	eat before %lu, now is %li\n", phil->id + 1, \
	last_meal, phil->last_meal + phil->room->time_to_die, time);
}

int	debug_all_eat(t_phil *phil)
{
	pthread_mutex_lock(phil->room->mutexprint);
	printf("All phil ate at least %i times.\n", phil->room->must_eat);
	if (pthread_mutex_unlock(phil->room->mutexprint) != 0)
		return (0);
	return (1);
}

void	debug_eat(t_phil *p, struct timeval b)
{
	struct timeval	s;

	s = p->room->start;
	printf("%li %i %s (ate : %i times)\n", get_time(s, b), \
	p->id, "is eating", p->number_of_times_eaten);
}
