/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:00:09 by jules             #+#    #+#             */
/*   Updated: 2023/01/31 16:42:40 by jules            ###   ########.fr       */
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

typedef struct s_data
{
	time_t  				ttd;
	time_t  				tte;
	time_t  				tts;
	int     				nb_philo;
	int     				nb_meal;
	pthread_mutex_t	*fork;
}   t_data;

typedef struct  s_philo
{
	int							id;
	int 						meals;
	time_t					last_meal;
	pthread_t				thread;
	pthread_mutex_t	left_hand;
	pthread_mutex_t	right_hand;
	t_data					data;
}   t_philo;

//Check Args
int 		check_args(int argc, char **argv);

//Init
int			init_data(int argc, char **argv, t_data *data);
int			init_philo(t_philo **philo, t_data *data);


//Events
void		eat(t_philo *philo);

//Utils
int			ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void 		print_error(char *str);

int	destroy_philo(t_philo **philo);

#endif
