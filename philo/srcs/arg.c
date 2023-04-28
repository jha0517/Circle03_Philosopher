/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:38:35 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/04 18:20:32 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_digital(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (!(ac == 5 || ac == 6))
		return (printf("./philo [num_philo] [die_ms] \
		[eat_ms] [sleep_ms] [opt:num_eat]\n"), 1);
	while (i < ac && ft_digital(av[i]))
		i++;
	if ((i != ac) && !ft_digital(av[i]))
		return (printf("Error: arguments has to be numeric\n"), 1);
	i = 1;
	while (i < ac && ft_atoi(av[i]) > 0)
		i++;
	if ((i != ac) && ft_atoi(av[i]) < 0)
		return (printf("Error: non positive value OR invalid input\n"), 1);
	return (0);
}
