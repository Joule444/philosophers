/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:59:46 by jules             #+#    #+#             */
/*   Updated: 2023/01/20 17:00:17 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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