/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:00:09 by jules             #+#    #+#             */
/*   Updated: 2023/01/17 14:20:01 by jules            ###   ########.fr       */
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

typedef struct s_data
{
    time_t  ttd;
    time_t  tte;
    time_t  tts;
    int     nb_philo;
    int     nb_meal;
}   t_data;

//Utils
int	ft_atoi(const char *str);

#endif