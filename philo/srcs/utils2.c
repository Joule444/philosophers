/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:32:31 by jthuysba          #+#    #+#             */
/*   Updated: 2023/03/14 10:19:00 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Check si la simu est destinee a mourir
// int	will_die(t_philo *philo)
// {
	// time_t	ttd;
	// time_t	tte;
	// time_t	tts;

	// ttd = philo->data->ttd;
	// tte = philo->data->tte;
	// tts = philo->data->tts;
// 	if (philo->data->nb_philo == 1)
// 		return (1);
// 	if (philo->data->nb_philo % 2 == 0)
// 	{
// 		if (ttd < tte + tts)
// 			return (1);
// 	}
// 	else
// 	{
// 		if (ttd < tte + tts + tte)
// 			return (1);
// 	}
// 	return (0);
// }

//Usleep en fonction de la simu
void	good_usleep(t_philo *philo)
{
	time_t	ttd;
	time_t	tte;
	time_t	tts;

	ttd = philo->data->ttd;
	tte = philo->data->tte;
	tts = philo->data->tts;
	if (ttd < tte && ttd < tts)
		my_usleep(ttd / 2, philo);
	else if (tte < ttd && tte < tts)
		my_usleep(tte / 2, philo);
	else
		my_usleep(tts / 2, philo);
}

//Active bool de fin
void	set_end(t_observer *observer)
{
	pthread_mutex_lock(&observer->end_access);
	observer->end = 1;
	pthread_mutex_unlock(&observer->end_access);
}
