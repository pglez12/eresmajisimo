/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:22:45 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:31:43 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *ph, long *start_time)
{
	int	ret;

	while (1)
	{
		pthread_mutex_lock(ph->left_mutex);
		if (!(*ph->left_fork))
		{
			pthread_mutex_unlock(ph->left_mutex);
			ret = ft_eat_right_mutex(ph, *start_time);
			if (ret == EXIT_SUCCESS)
				break ;
			if (ret == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			pthread_mutex_unlock(ph->left_mutex);
		if (ft_check_philo(ph, *start_time, NOT_PRINT) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		usleep(100);
	}
	*start_time = ft_time_now();
	if (ft_check_philo(ph, *start_time, EAT) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_pause_philo(ph, *start_time, ph->info.time_to_eat);
	return (EXIT_SUCCESS);
}

int	ft_sleep(t_philo *ph, long start_time)
{
	ft_padlock_fmutex(ph->left_mutex, ph->left_fork);
	ft_padlock_fmutex(ph->right_mutex, ph->right_fork);
	if (ft_check_philo(ph, start_time, SLEEP) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_pause_philo(ph, start_time, ph->info.time_to_sleep
		+ ph->info.time_to_eat);
	return (EXIT_SUCCESS);
}

int	ft_think(t_philo *ph, long start_time)
{
	if (ft_check_philo(ph, start_time, THINK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
