/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:53:10 by jules             #+#    #+#             */
/*   Updated: 2023/03/06 15:54:14 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval	current_time;
	time_t	time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

time_t	get_timestamp(t_data data)
{
	time_t					time;

	time = get_current_time();
	// time = 1;
	return (time - data.start_time);
}

void	print_state(t_philo philo, int state)
{
	long	ts;
	
	pthread_mutex_lock(&philo.data->micro);
	// if (check_end(philo) == 1)
	// {
	// 	pthread_mutex_unlock(&philo.data->micro);
	// 	return ;
	// }
	ts = 0;
	// ts = get_timestamp(*philo.data);s
	if (state == EATING)
		printf("%ld\t\033[31;01m%d is eating\033[00m\n", ts, philo.id + 1);
	else if (state == SLEEPING)
		printf("%ld\t\033[34;01m%d is sleeping\033[00m\n", ts, philo.id + 1);
	else if (state == THINKING)
		printf("%ld\t\033[32;01m%d is thinking\033[00m\n", ts, philo.id + 1);
	else if (state == HAS_TAKEN_A_FORK)
		printf("%ld\t\033[33;01m%d has taken a fork\033[00m\n", ts, philo.id + 1);
	else if (state == DIED)
		printf("%ld\t\033[30;01m%d died\033[00m\n", ts, philo.id + 1);
	pthread_mutex_unlock(&philo.data->micro);
}
