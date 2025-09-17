/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:24:15 by tracy             #+#    #+#             */
/*   Updated: 2025/09/17 09:24:54 by mezhang          ###   ########.fr       */
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
	if (!philo->data->one_die)
		printf("%lld %d %s\n", relative_time, philo->id, message);
	else if (strcmp(message, "died") == 0)
		printf("%lld %d %s\n", relative_time, philo->id, message);
	pthread_mutex_unlock(&(philo->data->print_lock));
}
