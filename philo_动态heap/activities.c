/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 00:20:20 by tracy             #+#    #+#             */
/*   Updated: 2025/09/17 09:42:38 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (get_is_end(philo->data))
	{
		take_off_forks(first, second);
		return ;
	}
}

void	self_check_death(t_philo *philo)
{
	long long	current_time;
	long long	since_last_meal;

	current_time = get_time();
	pthread_mutex_lock(&philo->lock);
	since_last_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->lock);
	if (since_last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->data->die_lock);
		if (!philo->data->one_die)
		{
			philo->data->one_die = 1;
			pthread_mutex_unlock(&philo->data->die_lock);
			safe_print(philo, "died");
			return ;
		}
		pthread_mutex_unlock(&philo->data->die_lock);
	}
}

void	philo_thinking(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

void	philo_eating(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->last_meal_time = get_time();
	philo->num_eaten += 1;
	pthread_mutex_unlock(&philo->lock);
	safe_print(philo, "is eating");
	precise_sleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	take_off_forks(first, second);
}

void	philo_sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	precise_sleep(philo->time_to_sleep, philo);
}
