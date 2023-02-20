/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jules             #+#    #+#             */
/*   Updated: 2023/02/20 17:28:42 by jthuysba         ###   ########.fr       */
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
	pthread_mutex_init(&(data->micro), NULL);
	data->observer.end = 0;
	pthread_mutex_init(&(data->observer.look_end), NULL);
	data->start_time = get_current_time(data);
	return (0);
}

int	init_philo(t_philo **philo, t_data *data)
{
	int	i;
	
	i = 0;
	*philo = malloc(sizeof(t_philo) * data->nb_philo - 1);
	if (!(*philo))
		return (print_error("Malloc error\n"));
	while (i < data->nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].meals = 0;
		(*philo)[i].last_meal = get_current_time(data);
		(*philo)[i].left_hand = &data->fork[i];
		if ((*philo)[i].id != 1)
		{
			(*philo)[i].right_hand = &data->fork[i - 1];
		}
		else
		{
			(*philo)[i].right_hand = &data->fork[data->nb_philo - 1];
		}
		i++;
	}
	return (0);
}
