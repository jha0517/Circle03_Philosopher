/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:08:29 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/04 18:22:30 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_if_sim_stop(t_phil *phil)
{
	pthread_mutex_lock(phil->room->mutexdeath);
	if (!phil->room->loop || phil->room->all_ate)
		return (pthread_mutex_unlock(phil->room->mutexdeath), 1);
	pthread_mutex_unlock(phil->room->mutexdeath);
	return (0);
}

int	ft_usleep(t_phil *phil, int time_to_sleep)
{
	struct timeval	start;
	struct timeval	end;
	unsigned int	i;

	if (time_to_sleep == -1)
		return (0);
	pthread_mutex_lock(phil->room->mutexlastmeal);
	i = phil->last_meal + phil->room->time_to_die;
	pthread_mutex_unlock(phil->room->mutexlastmeal);
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	while ((get_time(start, end) < (unsigned long)time_to_sleep))
	{
		usleep(100);
		gettimeofday(&end, NULL);
		if (i < get_time(phil->room->start, end))
		{
			pthread_mutex_lock(phil->room->mutexdeath);
			phil->room->loop = 0;
			pthread_mutex_unlock(phil->room->mutexdeath);
			return (DIED_OR_ALL_ATE);
		}
	}
	return (0);
}

void	starved_to_death(t_phil *phil, unsigned long deathtime)
{
	pthread_mutex_lock(phil->room->mutexdeath);
	phil->room->loop = 0;
	pthread_mutex_unlock(phil->room->mutexdeath);
	pthread_mutex_lock(phil->room->mutexprint);
	ft_write(deathtime, phil->id, DEAD);
	pthread_mutex_unlock(phil->room->mutexprint);
}

int	check_starvation(t_phil *phil)
{
	struct timeval	end;
	int				i;
	int				deadline;

	i = -1;
	while (++i < phil->room->number_of_philosophers)
	{
		gettimeofday(&end, NULL);
		pthread_mutex_lock(phil->room->mutexlastmeal);
		deadline = phil[i].last_meal + phil->room->time_to_die;
		pthread_mutex_unlock(phil->room->mutexlastmeal);
		if (deadline < (int)get_time(phil->room->start, end))
		{
			starved_to_death(&phil[i], get_time(phil->room->start, end));
			return (DIED_OR_ALL_ATE);
		}
	}
	return (0);
}

int	checker(t_phil *phil)
{
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(phil->room->mutexdeath);
		if (phil->room->all_ate)
			return (pthread_mutex_unlock(phil->room->mutexdeath), 9);
		pthread_mutex_unlock(phil->room->mutexdeath);
		if (check_starvation(phil))
		{
			pthread_mutex_lock(phil->room->mutexdeath);
			phil->room->loop = 0;
			pthread_mutex_unlock(phil->room->mutexdeath);
			return (DIED_OR_ALL_ATE);
		}
	}
	return (0);
}
