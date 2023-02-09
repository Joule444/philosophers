/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:24:06 by jules             #+#    #+#             */
/*   Updated: 2023/02/09 14:51:22 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo philo)
{
	long	time;

	time = get_current_time(philo.data);
	if (time - philo.last_meal > philo.data->ttd)
		return (1);
	else
		return (0);
}

void	*observer(void *param)
{
	t_philo	*philo;
	int			i;

	philo = param;
	while (philo->data->observer->end == 0)
	{
		// pthread_mutex_lock(&philo->data->micro);
		i = 0;
		while (i < philo->data->nb_philo && philo->data->observer->end == 0)
		{
			// printf("time=%ld\nlast_meal=%ld\nlast_meal - time=%ld\nttd=%ld\n", time, philo[i].last_meal, time - philo[i].last_meal, philo->data->ttd);
			if (is_dead(philo[i]))
			{
				// pthread_mutex_unlock(&philo->data->micro);
				// print_state(philo[i], DIED);
				printf("%d is dead\n", i + 1);
				// pthread_mutex_lock(&philo->data->micro);
				philo->data->observer->end = 1;
			}
			i++;
		}
		// pthread_mutex_unlock(&philo->data->micro);
		usleep(700);
	}
	return (NULL);
}
