/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:00:09 by jules             #+#    #+#             */
/*   Updated: 2023/03/06 17:48:33 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

enum	e_state
{
	EATING,
	SLEEPING,
	THINKING,
	HAS_TAKEN_A_FORK,
	DIED
};

typedef struct s_observer
{
	// pthread_t		thread;
	int				end;
	pthread_mutex_t	end_access;
}	t_observer;



typedef struct s_data
{
	time_t			start_time;
	time_t  		ttd;
	time_t  		tte;
	time_t  		tts;
	int     		nb_philo;
	int				max_meals;
	pthread_mutex_t	*fork;
	pthread_mutex_t	micro;
	t_observer		observer;
}	t_data;

typedef struct  s_philo
{
	int				id;
	int 			meals;
	time_t			last_meal;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

//Check Args
int 	check_args(int argc, char **argv);

//Init
int		init_data(int argc, char **argv, t_data *data);
t_philo	*init_philo(t_philo *philo, t_data *data);

void	print_state(t_philo *philo, int state);
time_t	get_current_time(void);
time_t	get_timestamp(t_data *data);
void	my_usleep(long time, t_philo philo);

//Events
void	eating(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2);
void	eating_prep(t_philo *philo);
void	sleeping(t_philo *philo);

//Observer
void	*observer(void *param);

int	check_end(t_philo philo);

//Utils
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		print_error(char *str);

#endif
