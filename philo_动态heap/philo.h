/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:41:56 by mezhang           #+#    #+#             */
/*   Updated: 2025/09/16 23:25:19 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include "philo_defines.h"


//parsing utils
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);

//init
int	init_locks(t_data **data);

//launch all
int		init_data(t_data *data, char **av, int ac, int num);
int			launch_forks(pthread_mutex_t **forks, int num);
int			launch_philos(t_data *data, pthread_mutex_t *forks, int num, char **av);
void	philos_start(t_data *data, int num);

//time
long long 	get_time(void);
void	precise_sleep(long long time_to_sleep, t_philo *philo);

//print
void	safe_print(t_philo *philo, const char *message);
void	print_status(t_philo *philo);

//activities
void	philo_thinking(t_philo *philo);
// void	philo_eating(t_philo *philo);
void	philo_eating(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second);
void	philo_sleeping(t_philo *philo);
void check_death(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second);
void self_check_death(t_philo *philo); // 🔧 新增：自检死亡函数

//use forks
void	get_forks_order(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second);
int	get_a_fork(t_philo *philo, pthread_mutex_t *fork);
int	get_both_forks(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second);
void	take_off_forks(pthread_mutex_t **first_fork, pthread_mutex_t **second_fork);

//routine
void	one_philo_routine(t_philo *philo);
void		*philo_routine(void *arg);
void	must_wait(t_philo *philo);

//neighbor protection
int			to_protect_neighbor(t_philo *current_philo, pthread_mutex_t *fork);

//monitoring
int	get_is_end(t_data *data);
// void	set_is_end(t_data *data, int value);
void 		monitoring(t_data *data, int num);
int	all_fed(t_data *data, int num);
int	is_philo_dead(t_philo *philo);

//clean up
void		cleanup(t_data *data, pthread_mutex_t *forks, int num);
void		stop_philos(t_data *data, int count);
void	free_forks(pthread_mutex_t *forks, int count);
void	free_philo_locks(t_data *data, int count);

#endif
