/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:08:41 by jules             #+#    #+#             */
/*   Updated: 2023/02/03 14:27:06 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	//Prends fork left et right
	pthread_mutex_lock(&philo->left_hand);
	print_state(*philo, HAS_TAKEN_A_FORK);
	pthread_mutex_lock(&philo->right_hand);
	print_state(*philo, HAS_TAKEN_A_FORK);
	print_state(*philo, EATING);
	usleep(philo->data.tte);
	pthread_mutex_unlock(&philo->left_hand);
	pthread_mutex_unlock(&philo->right_hand);
	philo->meals++;
}
