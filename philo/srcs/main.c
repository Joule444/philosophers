/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/01/31 18:06:53 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*routine(void *param)
// {
// 	t_philo *philo;

// 	philo = param;
// 	sleep(1);
// 	printf("Hello from thread %d\n", philo->id);
// 	sleep(1);
	
// 	if (philo->id % 2 != 0) //Premiere routine de demmarage si impair
// 	{
// 		eat(philo);
// 		printf("Philo %d meals count : %d\n", philo->id, philo->meals);
// 		printf("[time] %d is sleeping\n", philo->id);
// 		usleep(philo->data.tts);
// 		printf("[time] %d is thinking\n", philo->id);
// 	}
// 	else
// 	{
// 		printf("[time] %d is thinking\n", philo->id);
// 		usleep(philo->data.tte);
// 	}
// 	while (1)
// 	{
// 		eat(philo);
// 		printf("Philo %d meals count : %d\n", philo->id, philo->meals);
// 		printf("[time] %d is sleeping\n", philo->id);
// 		usleep(philo->data.tts);
// 		printf("[time] %d is thinking\n", philo->id);
// 	}
// 	return (NULL);
// }

void	*routine(void *param)
{
	t_philo *philo;
	
	philo = param;
	sleep(5);
	pthread_mutex_lock(&philo->left_hand);
	pthread_mutex_lock(&philo->right_hand);
	printf("%d take his forks\n", philo->id);
	sleep(5);
	pthread_mutex_unlock(&philo->right_hand);
	pthread_mutex_unlock(&philo->left_hand);
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
		printf("Thread %d created!\n", philo[i].id);
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
