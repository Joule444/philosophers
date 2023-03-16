/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:08:41 by jules             #+#    #+#             */
/*   Updated: 2023/03/16 15:32:03 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Philo prends une fork
void	take_fork(t_fork fork, t_philo *philo)
{
	pthread_mutex_lock(fork.a);
	print_state(philo, HAS_TAKEN_A_FORK);
}

//Eating event
void	eating(t_philo *philo, t_fork fork1, t_fork fork2)
{
	if (philo->id % 2 == 0)
	{
		take_fork(fork2, philo);
		take_fork(fork1, philo);
	}
	else if (philo->id % 2 != 0)
	{
		take_fork(fork1, philo);
		take_fork(fork2, philo);
	}
	print_state(philo, EATING);
	pthread_mutex_lock(&philo->data->meals_access[philo->id]);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meals_access[philo->id]);
	my_usleep(philo->data->tte, philo);
	pthread_mutex_lock(&philo->data->meals_access[philo->id]);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meals_access[philo->id]);
}

//Sleeping event
void	sleeping(t_philo *philo, t_fork fork1, t_fork fork2)
{
	pthread_mutex_unlock(fork2.a);
	pthread_mutex_unlock(fork1.a);
	print_state(philo, SLEEPING);
	my_usleep(philo->data->tts, philo);
}

//Thinking event
void	thinking(t_philo *philo)
{
	print_state(philo, THINKING);
	if (philo->data->nb_philo % 2 != 0)
		wait_hungry(philo);
}

//Attribu ses fourchettes a philo
void	eat_sleep(t_philo *philo)
{
	t_fork	fork1;
	t_fork	fork2;

	fork1.a = &philo->data->fork[philo->id];
	if (philo->id == philo->data->nb_philo - 1)
		fork2.a = &philo->data->fork[0];
	else
		fork2.a = &philo->data->fork[philo->id + 1];
	eating(philo, fork1, fork2);
	sleeping(philo, fork1, fork2);
}
