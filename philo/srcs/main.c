/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/02/09 14:52:55 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo *philo;

	philo = param;
	if (philo->id % 2 == 0) //Retarde les pairs pour faire commencer impairs
		usleep(300);
	while (philo->data->observer->end == 0)
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
	// if (pthread_create(&(philo->data->observer->thread), NULL, &observer, philo) != 0)
	// 		return (print_error("Thread create error\n"));
	while (i < philo->data->nb_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &routine, philo + i) != 0)
			return (print_error("Thread create error\n"));
		i++;
  }
	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (print_error("Thread join error\n"));
		i++;
	}
	// if (pthread_join(philo->data->observer->thread, NULL))
	// 	return (print_error("Thread join error\n"));
	return (0);
}

int main(int argc, char **argv)
{
	t_data  data;
	t_philo *philo;

	// printf ("\033[34;01mBonjour\033[00m\n");
	if (check_args(argc, argv) == 1)
		return (1);
	if (init_data(argc, argv, &data))
		return (2);
	if (init_philo(&philo, &data) == 1)
		return (3);
	if (philosophers(philo))
		return (4);
	free(data.fork);
	free(philo);
	return (0);
}
