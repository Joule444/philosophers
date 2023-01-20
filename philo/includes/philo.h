/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:00:09 by jules             #+#    #+#             */
/*   Updated: 2023/01/20 18:00:02 by jules            ###   ########.fr       */
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
	time_t  ttd;
	time_t  tte;
	time_t  tts;
	int     nb_philo;
	int     nb_meal;
}   t_data;

typedef struct  s_philo
{
	int	index;
	int meals;
	pthread_t   thread;
	t_data  data;
}   t_philo;

void print_error(char *str);

//Check Args
int check_args(int argc, char **argv);

//Utils
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *str);


#endif
