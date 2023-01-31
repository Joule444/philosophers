/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:08:41 by jules             #+#    #+#             */
/*   Updated: 2023/01/31 17:47:32 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	//Prends fork left et right
	pthread_mutex_lock(&philo->left_hand);
	printf("[time] %d has taken a fork\n", philo->id);
	pthread_mutex_lock(&philo->right_hand);
	printf("[time] %d has taken a fork\n", philo->id);
	printf("[time] %d is eating\n", philo->id);
	usleep(philo->data.tte);
	pthread_mutex_unlock(&philo->left_hand);
	pthread_mutex_unlock(&philo->right_hand);
	philo->meals++;
}
