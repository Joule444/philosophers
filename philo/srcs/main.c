/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/01/20 17:59:44 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

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

// void    philo(t_data data)
// {
//     t_philo *philo;
//     int i;
//
//     i = 0;
//     while (i <= data.nb_philo)
//     {
//         pthread_create();
//         i++;
//     }
// }

int	init_philo(t_philo **philo, t_data data)
{
	int	i;
	
	i = 0;
	*philo = malloc(sizeof(t_philo) * data.nb_philo);
	if (*philo == NULL)
		return (print_error("Malloc error\n"), 1);
	while (i < data.nb_philo)
	{
		philo[i]->index = i + 1;
		philo[i]->data = data;
		philo[i]->meals = 0;
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
	// philo(data);
	return (0);
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
