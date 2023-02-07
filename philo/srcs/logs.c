/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:53:10 by jules             #+#    #+#             */
/*   Updated: 2023/02/07 14:37:37 by jules            ###   ########.fr       */
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
	long	ts;
	long	time;
	
	ts = get_timestamp(*philo.data);
	time = get_current_time(philo.data);
	pthread_mutex_lock(&philo.data->micro);
	if (time - philo.last_meal > philo.data->ttd)
	{
		printf("[%ld] \033[30;01m%d died\033[00m\n", ts, philo.id);
		return ;
	}
	if (state == EATING)
		printf("[%ld] \033[31;01m%d is eating\033[00m\n", ts, philo.id);
	if (state == SLEEPING)
		printf("[%ld] \033[34;01m%d is sleeping\033[00m\n", ts, philo.id);
	if (state == THINKING)
		printf("[%ld] \033[32;01m%d is thinking\033[00m\n", ts, philo.id);
	if (state == HAS_TAKEN_A_FORK)
		printf("[%ld] \033[33;01m%d has taken a fork\033[00m\n", ts, philo.id);
	pthread_mutex_unlock(&philo.data->micro);
}
