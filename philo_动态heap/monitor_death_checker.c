/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:18:32 by tracy             #+#    #+#             */
/*   Updated: 2025/09/17 09:43:09 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_is_end(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->die_lock);
	value = data->one_die;
	pthread_mutex_unlock(&data->die_lock);
	return (value);
}
