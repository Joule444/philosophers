/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/03/13 20:38:47 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_hungry(t_philo *philo)
{
	while ((get_current_time() - philo->last_meal) < ((3 * philo->data->ttd) / 4))
	{
		my_usleep(50, philo);
	}
}

void	thinking(t_philo *philo)
{
	print_state(philo, THINKING);
	if (philo->data->nb_philo % 2 != 0)
		wait_hungry(philo);
}

//Routine des philos
void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->data->nb_philo == 1)
		return (print_state(philo, HAS_TAKEN_A_FORK), param);
	if (philo->id % 2 != 0)
		my_usleep(philo->data->tte / 3, philo);
	if (philo->data->nb_philo % 2 != 0 && philo->id == philo->data->nb_philo - 1)
		my_usleep(philo->data->tte / 2, philo);
	while (check_end(philo) == 0)
	{
		eat_sleep(philo);
		thinking(philo);
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
