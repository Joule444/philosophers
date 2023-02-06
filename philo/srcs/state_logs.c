/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:53:10 by jules             #+#    #+#             */
/*   Updated: 2023/02/06 14:48:23 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_current_time(t_data *data)
{
	time_t	time;

	gettimeofday(&data->current_time, NULL);
	time = (data->current_time.tv_sec * 1000) + data->current_time.tv_usec;
	return (time);
}

time_t	get_timestamp(t_data data)
{
	time_t					time;

	time = get_current_time(&data);
	return (time - data.start_time);
}

void	print_state(t_philo philo, int state)
{
	long	time;
	// printf ("\033[34;01mBonjour\033[00m\n");
	time = get_timestamp(philo.data);
	pthread_mutex_lock(&philo.data.log);
	if (state == EATING)
		printf("[%ld] \033[31;01m%d is eating\033[00m\n", time, philo.id);
	if (state == SLEEPING)
		printf("[%ld] \033[34;01m%d is sleeping\033[00m\n", time, philo.id);
	if (state == THINKING)
		printf("[%ld] \033[32;01m%d is thinking\033[00m\n", time, philo.id);
	if (state == HAS_TAKEN_A_FORK)
		printf("[%ld] \033[33;01m%d has taken a fork\033[00m\n", time, philo.id);
	pthread_mutex_unlock(&philo.data.log);
}
