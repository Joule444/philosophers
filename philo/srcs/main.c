/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/01/26 16:38:33 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo *philo;

	philo = param;
	sleep(1);
	printf("Hello from thread %d\n", philo->id);
	sleep(1);
	// if (philo->id % 2 != 0) //Si impair
		
	return (NULL);
}

int	philosophers(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data.nb_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &routine, philo + i) != 0)
			return (print_error("Thread create error\n"), 1);
		printf("Thread %d created!\n", philo[i].id);
		i++;
    }
	i = 0;
	while (i < philo->data.nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (print_error("Thread join error\n"), 1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data  data;
	t_philo *philo;

	if (check_args(argc, argv) == 1)
		return (1);
	init_data(argc, argv, &data);
	if (init_philo(&philo, data) == 1)
		return (2);
	if (philosophers(philo))
		return (3);
	if (destroy_philo(&philo))
		return (4);
	return (free(philo), 0);
}

// int mails = 0;

// void  *routine()
// {
//     printf("Test from threads\n");
//     for(int i = 0; i < 1000000; i++)
//         mails++;
//     printf("Ending thread\n");
//     return (NULL);
// }

// int main(int argc, char **argv)
// {
//     (void) argc;
//     (void) argv;
//     pthread_t   t1;
//     pthread_t   t2;
//     if (pthread_create(&t1, NULL, &routine, NULL) != 0)
//         return (1);
//     if (pthread_create(&t2, NULL, &routine, NULL) != 0)
//         return (1);
//     if (pthread_join(t1, NULL) != 0)
//         return (1);
//     if (pthread_join(t2, NULL) != 0)
//         return (1);
//     printf("mails : %d\n", mails);
//     return 0;
// }
