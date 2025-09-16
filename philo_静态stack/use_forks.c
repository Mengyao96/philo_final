/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:04:19 by tracy             #+#    #+#             */
/*   Updated: 2025/09/16 03:05:24 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks_order(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	*first = philo->r_fork;
	*second = philo->l_fork;
}

int	get_a_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (get_is_end(philo->data))
		return (0);
	pthread_mutex_lock(fork);
	if (get_is_end(philo->data))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	safe_print(philo, "has taken a fork");
	return (1);
}

int	get_both_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (!get_a_fork(philo, *first))
		return (0);
	if (!get_a_fork(philo, *second))
	{
		pthread_mutex_unlock(*first);
		return (0);
	}
	return (1);
}

void	take_off_forks(pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	pthread_mutex_unlock(*first_fork);
	pthread_mutex_unlock(*second_fork);
}
