/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:24:06 by jules             #+#    #+#             */
/*   Updated: 2023/02/07 14:38:20 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observer(void *param)
{
	t_philo	*philo;
	int			i;

	philo = param;
	i = 0;
	while (philo->data->observer->end == 0)
	{
		while (i < philo->data->nb_philo)
		{
			i++;
		}
	}
	return (NULL);
}
