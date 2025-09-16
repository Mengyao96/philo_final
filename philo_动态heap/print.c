/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:24:15 by tracy             #+#    #+#             */
/*   Updated: 2025/09/16 01:56:15 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, const char *message)
{
	long long	current_time;
	long long	relative_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->data->print_lock);
	relative_time = current_time - philo->start_time;
	if (!get_is_end(philo->data))
		printf("%lld %d %s\n", relative_time, philo->id, message);
	else if (strcmp(message, "died") == 0)
		printf("%lld %d %s\n", relative_time, philo->id, message);
	pthread_mutex_unlock(&(philo->data->print_lock));
}
