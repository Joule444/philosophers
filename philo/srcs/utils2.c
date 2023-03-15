/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:32:31 by jthuysba          #+#    #+#             */
/*   Updated: 2023/03/15 20:55:32 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Fais attendre un philo jusqua ce qu'il ait suffisament faim
void	wait_hungry(t_philo *philo)
{
	while ((get_current_time() - philo->last_meal)
		< ((3 * philo->data->ttd) / 4)
		&& check_end(philo) == 0)
		usleep(500);
}

//Active bool de fin
void	set_end(t_observer *observer)
{
	pthread_mutex_lock(&observer->end_access);
	observer->end = 1;
	pthread_mutex_unlock(&observer->end_access);
}
