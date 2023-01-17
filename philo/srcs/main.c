/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/01/17 16:56:07 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    set_data(int argc, char **argv, t_data *data)
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

int is_num(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

int check_args(int argc, char **argv)
{
    int i;

    i = 1;
    (void) argv;
    if (argc != 5 && argc != 6)
        return (1);
    while (argv[i])
    {
        if (is_num(argv[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_data  data;

    if (check_args(argc, argv) == 1)
        return(printf("Args error\n"), 1);
    set_data(argc, argv, &data);
    printf("nb_philo : %d\n", data.nb_philo);
    printf("ttd : %d\n", (int)data.ttd);
    printf("tte : %d\n", (int)data.tte);
    printf("tts : %d\n", (int)data.tts);
    printf("nb_meal : %d\n", data.nb_meal);
    return (0);
}

// void  *routine()
// {
//     printf("Test from threads\n");
//     sleep(3);
//     printf("Ending thread\n");
//     return (NULL);
// }

// int main(int argc, char **argv)
// {
//     (void) argc;
//     (void) argv;
//     pthread_t   t1;
//     pthread_t   t2;
//     pthread_create(&t1, NULL, &routine, NULL);
//     pthread_create(&t2, NULL, &routine, NULL);
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     return 0;
// }
