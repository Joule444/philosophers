/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:53:10 by jules             #+#    #+#             */
/*   Updated: 2023/02/20 17:42:48 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(t_data *data)
{
	time_t	time;

	gettimeofday(&data->current_time, NULL);
	time = (data->current_time.tv_sec * 1000) + (data->current_time.tv_usec / 1000);
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
	
	pthread_mutex_lock(&philo.data->micro);
	if (check_end(philo) == 1)
	{
		pthread_mutex_unlock(&philo.data->micro);
		return ;
	}
	ts = get_timestamp(*philo.data);
	if (state == EATING)
	{
		printf("[%ld] \033[31;01m%d is eating\033[00m\n", ts, philo.id);
		pthread_mutex_unlock(&philo.data->micro);
		philo.last_meal = get_current_time(philo.data);
		my_usleep(philo.data->tte * 1000, philo);
		return ;
	}
	if (state == SLEEPING)
	{
		printf("[%ld] \033[34;01m%d is sleeping\033[00m\n", ts, philo.id);
		pthread_mutex_unlock(&philo.data->micro);
		my_usleep(philo.data->tts * 1000, philo);
		return ;
	}
	if (state == THINKING)
		printf("[%ld] \033[32;01m%d is thinking\033[00m\n", ts, philo.id);
	if (state == HAS_TAKEN_A_FORK)
		printf("[%ld] \033[33;01m%d has taken a fork\033[00m\n", ts, philo.id);
	if (state == DIED)
		printf("[%ld] \033[30;01m%d died\033[00m\n", ts, philo.id);
	pthread_mutex_unlock(&philo.data->micro);
}
