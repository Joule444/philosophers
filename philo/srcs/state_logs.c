/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:53:10 by jules             #+#    #+#             */
/*   Updated: 2023/02/03 18:39:41 by jules            ###   ########.fr       */
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
	pthread_mutex_lock(&philo.data.state_log);
	if (state == EATING)
		printf("[%ld] %d is eating\n", (long) get_timestamp(philo.data), philo.id);
	if (state == SLEEPING)
		printf("[%ld] %d is sleeping\n", (long) get_timestamp(philo.data), philo.id);
	if (state == THINKING)
		printf("[%ld] %d is thinking\n", (long) get_timestamp(philo.data), philo.id);
	if (state == HAS_TAKEN_A_FORK)
		printf("[%ld] %d has taken a fork\n", (long) get_timestamp(philo.data), philo.id);
	pthread_mutex_unlock(&philo.data.state_log);
}
