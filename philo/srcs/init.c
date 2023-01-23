/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jules             #+#    #+#             */
/*   Updated: 2023/01/23 17:05:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_data(int argc, char **argv, t_data *data)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]); 
	data->tts = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meal = ft_atoi(argv[5]);
	else
		data->nb_meal = -1;
}

int	init_philo(t_philo **philo, t_data data)
{
	int	i;
	
	i = 0;
	*philo = malloc(sizeof(t_philo) * data.nb_philo);
	if (!(*philo))
		return (print_error("Malloc error\n"), 1);
	while (i < data.nb_philo)
	{
		(*philo)[i].index = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].meals = 0;
		i++;
	}
	return (0);
}
