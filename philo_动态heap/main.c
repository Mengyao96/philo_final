/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:41:46 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/16 23:25:19 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	*forks;
	int				num;

	if (argc < 5 || argc > 6)
		return (printf("Error: Too Few Arguments.\n"), 1);

	num = ft_atoi(argv[1]);
	if (init_data(&data, argv, argc, num) < 0)
		return (1);
	if (launch_forks(&forks, num) < 0)
		return (1);
	if (launch_philos(&data, forks, num, argv) < 0)
		return (1);

	philos_start(&data, num);
	monitoring(&data, num);
	cleanup(&data, forks, num);
	return (0);
}
