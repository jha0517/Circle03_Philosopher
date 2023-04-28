/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:07:47 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/12/02 18:24:53 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# define EATING 1
# define SLEEPING 4 
# define THINKING 0
# define FORK 2
# define DEAD 3
# define ERROR -100
# define DIED_OR_ALL_ATE 9

typedef struct s_room{
	pthread_mutex_t	*mutexprint;
	pthread_mutex_t	*mutexfork;
	pthread_mutex_t	*mutexdeath;
	pthread_mutex_t	*mutexlastmeal;
	struct timeval	start;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat;
	int				all_ate;
	int				total_number_of_times_eaten;
	int				ready;
	int				loop;
}	t_room;

typedef struct s_phil{
	unsigned long	last_meal;
	struct s_room	*room;
	int				id;
	int				number_of_times_eaten;
}	t_phil;

t_phil					*init(int ac, char **av);
unsigned long			get_time(struct timeval start, struct timeval stop);
void					*philosopher(void *v);
void					free_room(t_room *room);
void					free_phil(t_phil *phil);
int						check_arg(int ac, char **av);
int						ft_atoi(const char *str);
int						pickup(t_phil *phil);
int						putdown(t_phil *phil);
int						print_and_sleep(t_phil *phil, int state, int pause);
int						checker(t_phil *phil);
int						check_if_sim_stop(t_phil *phil);
int						check_if_sim_stop2(t_phil *phil);
int						ft_usleep(t_phil *phil, int time_to_sleep);
char					*ft_itoa(int nb);
size_t					ft_strlen(const char *str);
void					ft_putchar_fd(char c, int fd);
void					ft_putnbr_fd(int nb, int fd);
void					ft_putstr_fd(char *s, int fd);
int						destroy(t_phil *phil, pthread_t *threads, int len);
int						debug_all_eat(t_phil *phil);
void					debug_eat(t_phil *p, struct timeval b);
void					debug_dead(t_phil *phil, unsigned long time);
void					ft_write(unsigned int timestamp, int id, int state);
int						check_all_ate(t_phil *phil);

#endif
