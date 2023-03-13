/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:24:06 by jules             #+#    #+#             */
/*   Updated: 2023/03/13 20:51:52 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Verifie la booleenne de fin
int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->observer.end_access);
	if (philo->data->observer.end == 1)
	{
		pthread_mutex_unlock(&philo->data->observer.end_access);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->observer.end_access);
	return (0);
}

//Verifie si un philo est mort de faim
int	is_dead(t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(&philo->data->last_meal_access);
	time = get_current_time();
	if (time - philo->last_meal > philo->data->ttd)
	{
		pthread_mutex_unlock(&philo->data->last_meal_access);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->last_meal_access);
		return (0);
	}
}

//Check si tous les philos ont atteint le max de repas
int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (philo[i].meals < philo->data->max_meals)
			return (0);
		i++;
	}
	return (1);
}

int	will_die(t_philo *philo)
{
	time_t	ttd;
	time_t	tte;
	time_t	tts;

	ttd = philo->data->ttd;
	tte = philo->data->tte;
	tts = philo->data->tts;
	if (philo->data->nb_philo % 2 == 0)
	{
		if (ttd < tte + tts)
			return (1);
	}
	else
	{
		if (ttd < tte + tts + tte)
			return (1);
	}
	return (0);
}

//Routine du thread verifiant les conditions de fin
void	*observer(void *param)
{
	t_philo		*philo;
	int			i;

	philo = param;
	while (check_end(philo) == 0)
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			if (is_dead(&philo[i]))
			{
				print_state(&philo[i], DIED);
				pthread_mutex_lock(&philo->data->observer.end_access);
				philo->data->observer.end = 1;
				pthread_mutex_unlock(&philo->data->observer.end_access);
			}
			else if (philo->data->max_meals != -1 && check_meals(philo) == 1)
			{
				pthread_mutex_lock(&philo->data->observer.end_access);
				philo->data->observer.end = 1;
				pthread_mutex_unlock(&philo->data->observer.end_access);
			}
			i++;
		}
		if (will_die(philo) == 1)
			my_usleep(5, philo);
		else if (philo->data->tts < philo->data->tte)
			my_usleep(philo->data->tts, philo);
		else
			my_usleep(philo->data->tte, philo);
	}
	return (NULL);
}
