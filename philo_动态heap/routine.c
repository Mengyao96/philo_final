/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:53:12 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/17 09:42:19 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_routine(t_philo *philo)
{
	safe_print(philo, "has taken a fork");
	precise_sleep(philo->time_to_die + 1, philo);
	safe_print(philo, "died");
}

void	*philo_routine(void *param)
{
	t_philo			*philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)param;
	get_forks_order(philo, &first, &second);
	if (first == second)
		return (one_philo_routine(philo), NULL);
	if (philo->id % 2 == 0)
		precise_sleep(2, philo);
	while (!get_is_end(philo->data))
	{
		if (!get_both_forks(philo, &first, &second))
			break ;
		philo_eating(philo, &first, &second);
		if (get_is_end(philo->data))
			break ;
		philo_sleeping(philo);
		if (get_is_end(philo->data))
			break ;
		philo_thinking(philo);
	}
	return (NULL);
}

void	philos_start(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			printf("Error: Init threads failed.");
			return ;
		}
		i++;
	}
}
