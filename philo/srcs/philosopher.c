/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:39:45 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/02 17:59:25 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	print_message(t_phil *p, int state, struct timeval s, struct timeval before)
{
	if (check_if_sim_stop(p))
		return (DIED_OR_ALL_ATE);
	if (state != DEAD)
	{
		if (state == FORK)
			ft_write(get_time(s, before), p->id, state);
		ft_write(get_time(s, before), p->id, state);
		return (0);
	}
	pthread_mutex_lock(p->room->mutexdeath);
	p->room->loop = 0;
	pthread_mutex_unlock(p->room->mutexdeath);
	ft_write(get_time(s, before), p->id, state);
	return (DIED_OR_ALL_ATE);
}

int	print_and_sleep(t_phil *p, int state, int pause)
{
	struct timeval	before;

	gettimeofday(&before, NULL);
	pthread_mutex_lock(p->room->mutexprint);
	if (check_if_sim_stop(p))
		return (pthread_mutex_unlock(p->room->mutexprint), DIED_OR_ALL_ATE);
	if (state == FORK)
	{
		ft_write(get_time(p->room->start, before), p->id, state);
		ft_write(get_time(p->room->start, before), p->id, state);
		ft_write(get_time(p->room->start, before), p->id, EATING);
		pthread_mutex_lock(p->room->mutexlastmeal);
		p->last_meal = get_time(p->room->start, before);
		pthread_mutex_unlock(p->room->mutexlastmeal);
	}
	else if (print_message(p, state, p->room->start, before))
		return (pthread_mutex_unlock(p->room->mutexprint), DIED_OR_ALL_ATE);
	pthread_mutex_unlock(p->room->mutexprint);
	if (ft_usleep(p, pause))
	{
		return (DIED_OR_ALL_ATE);
	}
	return (0);
}

int	philosopher_loop(t_phil *phil)
{
	if (phil->id % 2 == 1)
		ft_usleep(phil, phil->room->time_to_eat);
	while (1)
	{
		if (pickup(phil))
		{
			pthread_mutex_lock(phil->room->mutexdeath);
			phil->room->loop = 0;
			pthread_mutex_unlock(phil->room->mutexdeath);
			if (phil->room->number_of_philosophers != 1)
				putdown(phil);
			break ;
		}
		putdown(phil);
		if (print_and_sleep(phil, SLEEPING, phil->room->time_to_sleep))
			break ;
		if (print_and_sleep(phil, THINKING, phil->room->time_to_think))
			break ;
	}
	return (0);
}

void	*philosopher(void *v)
{
	t_phil	*phil;

	phil = (t_phil *)v;
	philosopher_loop(phil);
	return (NULL);
}
