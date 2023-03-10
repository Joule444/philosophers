/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/03/10 17:02:17 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Routine des philos
void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->id % 2 == 0 || philo->id == 0)
		my_usleep(philo->data->tte, philo);
	while (check_end(philo) == 0)
	{
		eat_sleep(philo);
		print_state(philo, THINKING);
	}
	return (param);
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
	while (i < philo[0].data->nb_philo)
	{
		ret = pthread_create(&(philo[i].thread), NULL, &routine, &philo[i]);
		if (ret != 0)
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
	if (pthread_join(philo->data->observer.thread, NULL))
		return (print_error("Thread join error\n"));
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
		return (3);
	if (philosophers(philo))
		return (4);
	free(philo);
	free(data.fork);
	return (0);
}
