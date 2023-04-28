/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:33:38 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/02 17:15:39 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_write(unsigned int timestamp, int id, int state)
{
	char	*msg[5];
	int		size[5];

	msg[0] = " is thinking\n";
	msg[1] = " is eating\n";
	msg[2] = " has taken a fork\n";
	msg[3] = " died\n";
	msg[4] = " is sleeping\n";
	size[0] = 13;
	size[1] = 11;
	size[2] = 18;
	size[3] = 6;
	size[4] = 13;
	ft_putnbr_fd((int)timestamp, 1);
	write(1, " ", 1);
	ft_putnbr_fd(id + 1, 1);
	write(1, msg[state], size[state]);
}

int	are_you_lefty_or_righty(t_phil *phil)
{
	int				right;

	right = ((phil->id + phil->room->number_of_philosophers) - 1) \
	% phil->room->number_of_philosophers;
	if (phil->id % 2 == 0)
	{
		if (phil->room->number_of_philosophers == 1)
		{
			ft_usleep(phil, phil->room->time_to_die);
			return (ERROR);
		}
		pthread_mutex_lock(&(phil->room->mutexfork[phil->id]));
		pthread_mutex_lock(&(phil->room->mutexfork[right]));
	}
	else if (phil->id % 2 == 1)
	{
		pthread_mutex_lock(&(phil->room->mutexfork[right]));
		pthread_mutex_lock(&(phil->room->mutexfork[phil->id]));
	}
	return (0);
}

int	check_all_ate(t_phil *phil)
{
	int	ate;
	int	a;

	ate = 0;
	if (phil->room->must_eat != -1)
	{
		if ((phil->room->must_eat * phil->room->number_of_philosophers) \
		<= phil->room->total_number_of_times_eaten)
		{
			a = -1;
			while (++a < phil->room->number_of_philosophers)
				ate ++;
		}
		if (ate == phil->room->number_of_philosophers)
		{
			pthread_mutex_lock(phil->room->mutexdeath);
			phil->room->all_ate = 1;
			pthread_mutex_unlock(phil->room->mutexdeath);
			return (DIED_OR_ALL_ATE);
		}
	}
	return (0);
}

int	pickup(t_phil *phil)
{
	if (are_you_lefty_or_righty(phil))
		return (ERROR);
	if (check_if_sim_stop(phil))
		return (DIED_OR_ALL_ATE);
	print_and_sleep(phil, FORK, -1);
	pthread_mutex_lock(phil->room->mutexlastmeal);
	phil->number_of_times_eaten += 1;
	phil->room->total_number_of_times_eaten += 1;
	if (check_all_ate(phil))
		return (pthread_mutex_unlock(phil->room->mutexlastmeal), \
		DIED_OR_ALL_ATE);
	pthread_mutex_unlock(phil->room->mutexlastmeal);
	if (ft_usleep(phil, phil->room->time_to_eat))
		return (DIED_OR_ALL_ATE);
	return (0);
}

int	putdown(t_phil *phil)
{
	int	right;
	int	total;

	total = phil->room->number_of_philosophers;
	right = ((phil->id + total) - 1) % total;
	if (phil->id % 2 == 0)
	{
		pthread_mutex_unlock(&(phil->room->mutexfork[phil->id]));
		pthread_mutex_unlock(&(phil->room->mutexfork[right]));
	}
	else if (phil->id % 2 == 1)
	{
		pthread_mutex_unlock(&(phil->room->mutexfork[right]));
		pthread_mutex_unlock(&(phil->room->mutexfork[phil->id]));
	}
	return (0);
}
