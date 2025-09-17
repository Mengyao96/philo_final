/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:18:32 by tracy             #+#    #+#             */
/*   Updated: 2025/09/17 09:50:25 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_fed(t_data *data, int num)
{
	int	num_fed;
	int	i;

	i = 0;
	num_fed = 0;
	if (data->philos[0].num_must_eat == -1)
		return (0);
	while (i < num)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if (data->philos[i].num_eaten >= data->philos[i].num_must_eat)
			num_fed++;
		pthread_mutex_unlock(&data->philos[i].lock);
		i++;
	}
	if (num_fed == num)
	{
		pthread_mutex_lock(&data->die_lock);
		data->one_die = 1;
		pthread_mutex_unlock(&data->die_lock);
		return (1);
	}
	return (0);
}

int	is_philo_dead(t_philo *philo)
{
	long long	current_time;
	long long	time_since_meal;
	int			is_eating;

	current_time = get_time();
	pthread_mutex_lock(&philo->lock);
	time_since_meal = current_time - philo->last_meal_time;
	is_eating = philo->eating;
	pthread_mutex_unlock(&philo->lock);
	if (time_since_meal > philo->time_to_die && !is_eating)
	{
		pthread_mutex_lock(&philo->data->die_lock);
		if (!philo->data->one_die)
		{
			philo->data->one_die = 1;
			pthread_mutex_unlock(&philo->data->die_lock);
			safe_print(philo, "died");
			return (1);
		}
		pthread_mutex_unlock(&philo->data->die_lock);
		return (1);
	}
	return (0);
}

int	check_philo_death(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (is_philo_dead(&data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	monitoring(t_data *data, int num)
{
	int	should_continue;

	should_continue = 1;
	while (should_continue)
	{
		if (check_philo_death(data, num) || all_fed(data, num))
			break ;
		pthread_mutex_lock(&data->die_lock);
		should_continue = !data->one_die;
		pthread_mutex_unlock(&data->die_lock);
		usleep(1000);
	}
}
