/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:18:32 by tracy             #+#    #+#             */
/*   Updated: 2025/09/16 02:58:41 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// only set variable, not print

int	get_is_end(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->die_lock);
	value = data->one_die;
	pthread_mutex_unlock(&data->die_lock);
	return (value);
}

// void	set_is_end(t_data *data, int value)
// {
// 	pthread_mutex_lock(&data->die_lock);
// 	data->one_die = value;
// 	pthread_mutex_unlock(&data->die_lock);
// }
