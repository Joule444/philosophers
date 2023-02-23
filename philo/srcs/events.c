/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:08:41 by jules             #+#    #+#             */
/*   Updated: 2023/02/23 16:19:12 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eating(t_philo *philo)
{	
	pthread_mutex_lock(philo->right_hand);
	print_state(*philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(philo->left_hand);
	print_state(*philo, HAS_TAKEN_A_FORK);
	print_state(*philo, EATING);
	philo->last_meal = get_current_time();
	// pthread_mutex_lock(&philo->data->tte_access);
	my_usleep(philo->data->tte * 1000, *philo);
	// pthread_mutex_unlock(&philo->data->tte_access);
	philo->meals++;
	// printf("[%ld] Philo %d ate his meal %d\n", get_timestamp(*philo->data), philo->id, philo->meals);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_hand);
	pthread_mutex_unlock(philo->right_hand);
	print_state(*philo, SLEEPING);
	// pthread_mutex_lock(&philo->data->tts_access);
	my_usleep(philo->data->tts * 1000, *philo);
	// pthread_mutex_unlock(&philo->data->tts_access);
}
