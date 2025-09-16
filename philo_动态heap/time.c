/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:12:11 by tracy             #+#    #+#             */
/*   Updated: 2025/09/16 03:05:35 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		current_ms;

	gettimeofday(&tv, NULL);
	current_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (current_ms);
}

void	precise_sleep(long long time_to_sleep, t_philo *philo)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_to_sleep)
	{
		if (get_is_end(philo->data))
			return ;
		usleep(500);
	}
}
