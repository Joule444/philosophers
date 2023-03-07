/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:24:06 by jules             #+#    #+#             */
/*   Updated: 2023/03/07 17:25:26 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	is_dead(t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(&philo->data->last_meal_access);
	time = get_current_time();
	if (time - philo->last_meal > philo->data->ttd) //Dead
		return (pthread_mutex_unlock(&philo->data->last_meal_access), 1);
	else
		return (pthread_mutex_unlock(&philo->data->last_meal_access), 0);
}

int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (philo->meals < philo->data->max_meals)
			return (0);
		i++;
	}
	return (1);
}

void	*observer(void *param)
{
	t_philo	*philo;
	int			i;

	philo = param;
	while (check_end(philo) == 0)
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			if (is_dead(&philo[i]))
			{
				pthread_mutex_lock(&philo->data->observer.end_access);
				philo->data->observer.end = 1;
				pthread_mutex_unlock(&philo->data->observer.end_access);
			}
			i++;
		}
		// my_usleep(700, philo);
		usleep(700);
	}
	return (NULL);
}
