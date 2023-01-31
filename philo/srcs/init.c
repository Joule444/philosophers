/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jules             #+#    #+#             */
/*   Updated: 2023/01/31 17:00:53 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

	data->nb_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]); 
	data->tts = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meal = ft_atoi(argv[5]);
	else
		data->nb_meal = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (print_error("Malloc error\n"), 1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&(data->fork[i]), NULL);
		i++;
	}
	return (0);
}

int	destroy_philo(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)[i].data.nb_philo)
	{
		// pthread_mutex_destroy(&(*philo)[i].left_hand);
		// pthread_mutex_destroy(&(*philo)[i].right_hand);
		// // if (pthread_join((*philo)[i].thread, NULL) != 0)
		// // 	return (print_error("Thread join error\n"), 1);
		i++;
	}
	return (0);
}

int	init_philo(t_philo **philo, t_data *data)
{
	int	i;
	
	i = 0;
	*philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!(*philo))
		return (print_error("Malloc error\n"), 1);
	while (i < data->nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = *data;
		(*philo)[i].meals = 0;
		(*philo)[i].left_hand = data->fork[i];
		printf("Philo %d left hand is fork %d\n", (*philo)[i].id, i + 1);
		if ((*philo)[i].id != 1)
		{
			(*philo)[i].right_hand = data->fork[i - 1];
			printf("Philo %d right hand is fork %d\n", (*philo)[i].id, i);
		}
		else
		{
			(*philo)[i].right_hand = data->fork[data->nb_philo - 1];
			printf("Philo %d right hand is fork %d\n", (*philo)[i].id, data->nb_philo);
		}
		i++;
	}
	return (0);
}
