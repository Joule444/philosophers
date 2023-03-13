/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:08:41 by jules             #+#    #+#             */
/*   Updated: 2023/03/13 14:51:18 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Eating event
void	eating(t_philo *philo, t_fork fork1, t_fork fork2)
{
	// if (philo->id % 2 != 0)
	// {
	// 	pthread_mutex_lock(fork1.a);
	// 	print_state(philo, HAS_TAKEN_A_FORK);
	// 	pthread_mutex_lock(fork2.a);
	// 	print_state(philo, HAS_TAKEN_A_FORK);
	// }
	// else
	// {
	// 	pthread_mutex_lock(fork2.a);
	// 	print_state(philo, HAS_TAKEN_A_FORK);
	// 	pthread_mutex_lock(fork1.a);
	// 	print_state(philo, HAS_TAKEN_A_FORK);
	// }
	pthread_mutex_lock(fork2.a);
	print_state(philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(fork1.a);
	print_state(philo, HAS_TAKEN_A_FORK);
	print_state(philo, EATING);
	pthread_mutex_lock(&philo->data->last_meal_access);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->last_meal_access);
	my_usleep(philo->data->tte, philo);
	philo->meals++;
}

//Sleeping event
void	sleeping(t_philo *philo, t_fork fork1, t_fork fork2)
{
	pthread_mutex_unlock(fork2.a);
	pthread_mutex_unlock(fork1.a);
	print_state(philo, SLEEPING);
	my_usleep(philo->data->tts, philo);
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
