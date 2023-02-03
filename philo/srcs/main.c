/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/02/03 17:02:46 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_timestamp(t_data data)
{
	struct timeval	current_time;
	time_t					time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + current_time.tv_usec;
	return (time - data.start_time);
}

void	print_state(t_philo philo, int state)
{
	pthread_mutex_lock(&philo.data.state_log);
	if (state == EATING)
	{
		printf("[%ld] %d is eating\n", (long) get_timestamp(philo.data), philo.id);
	}
	if (state == SLEEPING)
	{
		printf("[%ld] %d is sleeping\n", (long) get_timestamp(philo.data), philo.id);
	}
	if (state == THINKING)
	{
		printf("[%ld] %d is thinking\n", (long) get_timestamp(philo.data), philo.id);
	}
	if (state == HAS_TAKEN_A_FORK)
	{
		printf("[%ld] %d has taken a fork\n", (long) get_timestamp(philo.data), philo.id);
	}
	pthread_mutex_unlock(&philo.data.state_log);
}

void	*routine(void *param)
{
	t_philo *philo;

	philo = param;
	if (philo->id % 2 != 0) //Premiere routine de demmarage si impair
	{
		eating(philo);
		sleeping(philo);
		print_state(*philo, THINKING);
	}
	else
		usleep(300);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		print_state(*philo, THINKING);
	}
	return (NULL);
}

int	philosophers(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data.nb_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &routine, philo + i) != 0)
			return (print_error("Thread create error\n"), 1);
		i++;
    }
	i = 0;
	while (i < philo->data.nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (print_error("Thread join error\n"), 1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data  data;
	t_philo *philo;

	if (check_args(argc, argv) == 1)
		return (1);
	if (init_data(argc, argv, &data))
		return (2);
	if (init_philo(&philo, &data) == 1)
		return (3);
	if (philosophers(philo))
		return (4);
	// if (destroy_philo(&philo))
	// 	return ();
	return (free(philo), 0);
}
