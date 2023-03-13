/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:59:38 by jules             #+#    #+#             */
/*   Updated: 2023/03/13 20:58:38 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Check si c est un digit
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//Converti un num str en int
long	ft_atoi(const char *str)
{
	long	    i;
	long		res;
	long		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (sign * res);
}

//Retourne la taille d'une string
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//Usleep qui se stop si condition de fin
void	my_usleep(long time, t_philo *philo)
{
	long	t;
	long	goal;
	
	t = get_current_time();
	goal = t + time;
	while (t < goal)
	{
		if (check_end(philo) == 1)
			return ;
		usleep(50);
		t = get_current_time();
	}
}

//Print une erreur sur la sortie d'erreur
int print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
