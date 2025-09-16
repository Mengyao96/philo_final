/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 00:04:41 by tracy             #+#    #+#             */
/*   Updated: 2025/09/16 02:45:46 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	input_check(char **av)
{
		int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av, int ac, int num)
{
	(void)ac; // 避免unused参数警告
	if (input_check(av) != 0)
		return (printf("Error: Must be positive digits.\n"), -1);
	ft_memset(data, 0, sizeof(t_data));

	if (num < 1 || num > 200)
		return (printf("Error: Number of philosophers must be 1-200.\n"), -1);

	if (pthread_mutex_init(&(data->print_lock), NULL) != 0)
		return (printf("Error: Failed to init print_lock.\n"), -1);
	if (pthread_mutex_init(&(data->die_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->print_lock));
		return (printf("Error: Failed to init die_lock.\n"), -1);
	}
	if (pthread_mutex_init(&(data->eat_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(data->print_lock));
		pthread_mutex_destroy(&(data->die_lock));
		return (printf("Error: Failed to init eat_lock.\n"), -1);
	}
	return (0);
}
