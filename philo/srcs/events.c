/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:08:41 by jules             #+#    #+#             */
/*   Updated: 2023/02/03 16:57:44 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	//Prends fork left et right
	pthread_mutex_lock(&philo->left_hand);
	print_state(*philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->right_hand);
	print_state(*philo, HAS_TAKEN_A_FORK);
	print_state(*philo, EATING);
	usleep(philo->data.tte * 1000);
	philo->meals++;
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_hand);
	pthread_mutex_unlock(&philo->right_hand);
	print_state(*philo, SLEEPING);
	usleep(philo->data.tts * 1000);
}