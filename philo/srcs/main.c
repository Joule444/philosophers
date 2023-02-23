/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/02/23 16:44:11 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *param)
{
	t_philo *philo;

	philo = param;
	// printf("Thread %d created\n", philo->id);
	if (philo->id % 2 == 0) //Retarde les pairs pour faire commencer impairs
		my_usleep(300, *philo);
	while (check_end(*philo) == 0)
	{
		eating(philo);
		sleeping(philo);
		print_state(*philo, THINKING);
	}
	return (param);
}

int	philosophers(t_philo *philo)
{
	int i;
	
	i = 0;
	// if (pthread_create(&(philo->data->observer->thread), NULL, &observer, philo) != 0)
	// 		return (print_error("Thread create error\n"));
	while (i < philo[0].data->nb_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &routine, &philo[i]) != 0)
			return (print_error("Thread create error\n"));
		i++;
  	}
	i = 0;
	while (i < philo[0].data->nb_philo)
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

	philo = NULL;
	if (check_args(argc, argv) == 1)
		return (1);
	if (init_data(argc, argv, &data))
		return (2);
	philo = init_philo(philo, &data);
	if (philo == NULL)
		return (3);
	// if (philosophers(philo))
	// 	return (4);
	free(philo);
	free(data.fork);
	return (0);
}
