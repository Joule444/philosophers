/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:08:41 by jules             #+#    #+#             */
/*   Updated: 2023/02/24 17:41:29 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->id]);	//Right Hand
	print_state(*philo, HAS_TAKEN_A_FORK);
	if (philo->id == philo->data->nb_philo - 1)			//Left Hand
		pthread_mutex_lock(&philo->data->fork[0]);
	else
		pthread_mutex_lock(&philo->data->fork[philo->id + 1]);
	print_state(*philo, HAS_TAKEN_A_FORK);
	
	print_state(*philo, EATING);
	philo->last_meal = get_current_time();
	my_usleep(philo->data->tte * 1000, *philo);
	philo->meals++;
	 
	pthread_mutex_unlock(&philo->data->fork[philo->id]);
	if (philo->id == philo->data->nb_philo - 1)
		pthread_mutex_unlock(&philo->data->fork[0]);
	else
		pthread_mutex_unlock(&philo->data->fork[philo->id + 1]);
}

void	sleeping(t_philo *philo)
{
	
	print_state(*philo, SLEEPING);
	my_usleep(philo->data->tts * 1000, *philo);
}
