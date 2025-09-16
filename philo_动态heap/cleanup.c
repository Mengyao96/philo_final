/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:55:46 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/16 23:25:19 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	return ;
}

void	free_philo_locks(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(data->philos[i].lock));
		i++;
	}
}

void	stop_philos(t_data *data, int count)
{
	int	i;

	data->one_die = 1; // 替代set_is_end
	i = 0;
	while (i < count)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

void	cleanup(t_data *data, pthread_mutex_t *forks, int num)
{
	if (data->philos)
	{
		stop_philos(data, num);
		free_philo_locks(data, num);
		free(data->philos);
		data->philos = NULL;
	}
	// Dynamic forks allocation - need to destroy and free
	if (forks)
		free_forks(forks, num);

	pthread_mutex_destroy(&(data->print_lock));
	pthread_mutex_destroy(&(data->die_lock));
	pthread_mutex_destroy(&(data->eat_lock));
}
