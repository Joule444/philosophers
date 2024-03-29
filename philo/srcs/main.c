/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/03/23 13:54:36 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Routine des philos
void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->data->nb_philo == 1)
		return (print_state(philo, HAS_TAKEN_A_FORK), param);
	if (philo->id % 2 != 0)
		usleep(500);
	while (check_end(philo) == 0)
	{
		eat_sleep(philo);
		thinking(philo);
		if (check_end(philo) == 0)
			usleep(100);
	}
	return (param);
}

//Join tous les threads deja crees si un echoue
void	thread_join_error(t_philo *philo, int failed)
{
	int	i;

	i = 0;
	while (i < failed)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->data->observer.thread, NULL);
}

//Creation de tous les threads du programme (philos + observer)
int	philosophers(t_philo *philo)
{
	int	i;
	int	ret;

	i = 0;
	ret = pthread_create(&philo->data->observer.thread, NULL, &observer, philo);
	if (ret != 0)
		return (print_error("Thread create error\n"));
	while (i < philo->data->nb_philo)
	{
		ret = pthread_create(&(philo[i].thread), NULL, &routine, &philo[i]);
		if (ret != 0)
		{
			thread_join_error(philo, i);
			return (print_error("Thread create error\n"));
		}
		i++;
	}
	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->data->observer.thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (check_args(argc, argv) == 1)
		return (1);
	if (init_data(argc, argv, &data))
		return (2);
	philo = init_philo(philo, &data);
	if (philo == NULL)
		return (free(data.fork), free(data.meals_access), 3);
	if (philosophers(philo))
		return (4);
	free(philo);
	free(data.fork);
	free(data.meals_access);
	return (0);
}
