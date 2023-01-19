/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:56:52 by jules             #+#    #+#             */
/*   Updated: 2023/01/19 18:27:33 by jules            ###   ########.fr       */
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

void    *routine(void* data)
{
    t_data  *data1;

    data1 = (t_data *)data;
    while (1)
    {
        printf("Philo start eating\n");
        sleep(data1->tte);
        printf("Philo start sleeping\n");
        sleep(data1->tts);
        printf("Philo start thinking\n");
        sleep(1);
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_data  data;
    pthread_t   t1;

    if (check_args(argc, argv) == 1)
        return(printf("Args error\n"), 1);
    set_data(argc, argv, &data);
    if (pthread_create(&t1, NULL, routine, &data) != 0)
        return (2);
    if (pthread_join(t1, NULL))
        return (3);
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
