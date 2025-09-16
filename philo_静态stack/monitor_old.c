/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:18:32 by tracy             #+#    #+#             */
/*   Updated: 2025/09/16 01:52:20 by tracy            ###   ########.fr       */
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

	current_time = get_time();
	pthread_mutex_lock(&philo->lock);
	time_since_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->lock);
	
	if (time_since_meal > philo->time_to_die && !philo->eating)
	{
		pthread_mutex_lock(&philo->data->die_lock);
		if (!philo->data->one_die)
		{
			philo->data->one_die = 1;
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%lld %d died\n", current_time - philo->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_lock);
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
	while (!data->one_die)
	{
		if (check_philo_death(data, num) || all_fed(data, num))
			break;
		usleep(1000);
	}
}

#include "philo.h"

int	all_fed(t_philo *philos, int num)
{
	int	num_fed;
	int	i;

	i = 0;
	num_fed = 0;
	while (i < num)
	{
		pthread_mutex_lock(&(philos[i].eat_lock));
		if (philos[i].num_eaten >= philos[i].num_must_eat)
			num_fed++;
		pthread_mutex_unlock(&(philos[i].eat_lock));
		i++;
	}
	if (num_fed == num)
	{
		pthread_mutex_lock(&(philos[i].die_lock));
		*(philos[i].dead) = 1;
		pthread_mutex_unlock(&(philos[i].die_lock));
		return (1);
	}
	return (0);
}


int	is_dead(t_philo philo)
{
	pthread_mutex_lock(philo.eat_lock);
	if ((get_time() - philo.last_meal_time >= philo.time_to_die)
		&& philo.num_eaten == 0)
	{
		pthread_mutex_unlock(philo.eat_lock);
		return (1);
	}
	pthread_mutex_unlock(philo.eat_lock);
	return (0);
}


int	check_philo_death(t_philo *philos, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (is_dead(philos[i]))
		{
			safe_print(&(philos[i]), "died");
			pthread_mutex_lock(&(philos[i].die_lock));
			*(philos[i].dead) = 1;
			pthread_mutex_unlock(&(philos[i].die_lock));
			return (1);
		}
		i++;
	}
	return (0);
}


void	monitoring(t_data *data, int num)
{
	while (1)
	{
		if (check_philo_death(data->philos, num) || all_fed(data->philos, num))
			return ;
	}
}
