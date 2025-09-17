/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:46:29 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/17 09:47:47 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_forks(pthread_mutex_t **forks, int num)
{
	int	i;

	i = 0;
	*forks = malloc(sizeof(pthread_mutex_t) * num);
	if (!*forks)
		return (printf("Failed to malloc forks.\n"), -1);
	while (i < num)
	{
		if (pthread_mutex_init(&((*forks)[i]), NULL) != 0)
		{
			return (printf("Error: Failed to init forks[%d].\n", i), -1);
		}
		i++;
	}
	return (0);
}

void	setup_philo(t_data *data, pthread_mutex_t *forks, char **av)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		ft_memset(&(data->philos[i]), 0, sizeof(t_philo));
		philos[i].id = i + 1;
		if (av[5])
			philos[i].num_must_eat = ft_atoi(av[5]);
		else
			philos[i].num_must_eat = -1;
		philos[i].start_time = get_time();
		philos[i].last_meal_time = get_time();
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		philos[i].data = data;
		philos[i].l_fork = &(forks[i]);
		philos[i].r_fork = &(forks[(i + 1) % ft_atoi(av[1])]);
		if (pthread_mutex_init(&philos[i].lock, NULL) != 0)
			return ;
		i++;
	}
}

int	launch_philos(t_data *data, pthread_mutex_t *forks, int num, char **av)
{
	data->philos = malloc(sizeof(t_philo) * num);
	if (!data->philos)
		return (printf("Error: Failed to malloc philos.\n"), -1);
	setup_philo(data, forks, av);
	return (0);
}
