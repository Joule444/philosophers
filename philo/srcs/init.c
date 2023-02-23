/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jules             #+#    #+#             */
/*   Updated: 2023/02/23 16:44:01 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;
	
	data->nb_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]); 
	data->tts = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (print_error("Malloc error\n"));
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&(data->fork[i]), NULL);
		i++;
	}
	data->observer.end = 0;
	pthread_mutex_init(&(data->micro), NULL);
	pthread_mutex_init(&(data->observer.end_access), NULL);
	// pthread_mutex_init(&(data->start_time_access), NULL);
	// pthread_mutex_init(&(data->tte_access), NULL);
	// pthread_mutex_init(&(data->tts_access), NULL);
	data->start_time = get_current_time();
	return (0);
}

t_philo *init_philo(t_philo *philo, t_data *data)
{
	int	i;
	
	i = 0;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (print_error("Malloc error\n"), NULL);
	while (i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].left_hand = &data->fork[i];
		printf("Philo %d take fork %d in his left hand\n", philo[i].id, i);
		if (philo[i].id != 1)
		{
			philo[i].right_hand = &data->fork[i - 1];
			printf("Philo %d take fork %d in his right hand\n", philo[i].id, i - 1);
		}
		else
		{
			philo[i].right_hand = &data->fork[data->nb_philo - 1];
			printf("Philo %d take fork %d in his right hand\n", philo[i].id, data->nb_philo - 1);
		}
		philo[i].last_meal = philo->data->start_time;
		i++;
	}
	return (philo);
}

