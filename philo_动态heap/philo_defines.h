/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 09:51:17 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/17 10:00:17 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEFINES_H
# define PHILO_DEFINES_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_data
{
	int				one_die;
	struct s_philo	*philos;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				num_eaten;
	int				eating;
	int				num_must_eat;

	long long		start_time;
	long long		last_meal_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;

	t_data			*data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;

}					t_philo;

#endif
