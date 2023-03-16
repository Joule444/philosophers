/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:24:06 by jules             #+#    #+#             */
/*   Updated: 2023/03/16 15:51:38 by jthuysba         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->data->meals_access[philo->id]);
	time = get_current_time();
	if (time - philo->last_meal > philo->data->ttd)
	{
		pthread_mutex_unlock(&philo->data->meals_access[philo->id]);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->meals_access[philo->id]);
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
		pthread_mutex_lock(&philo->data->meals_access[philo[i].id]);
		if (philo[i].meals < philo->data->max_meals)
		{
			pthread_mutex_unlock(&philo->data->meals_access[philo[i].id]);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->meals_access[philo[i].id]);
		i++;
	}
	return (1);
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
				set_end(&philo->data->observer);
			}
			else if (philo->data->max_meals != -1 && check_meals(philo) == 1)
				set_end(&philo->data->observer);
			if (check_end(philo) == 0)
				usleep(500);
			i++;
		}	
	}
	return (NULL);
}
