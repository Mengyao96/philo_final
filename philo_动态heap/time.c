/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:12:11 by tracy             #+#    #+#             */
/*   Updated: 2025/09/17 09:37:00 by mezhang          ###   ########.fr       */
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

	(void)philo;
	start_time = get_time();
	while ((get_time() - start_time) < time_to_sleep)
	{
		usleep(500);
	}
}
