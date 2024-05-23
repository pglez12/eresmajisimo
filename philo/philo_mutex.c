/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:24:13 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:31:24 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat_right_mutex(t_philo *ph, long start_time)
{
	pthread_mutex_lock(ph->right_mutex);
	if (*ph->right_fork)
	{
		pthread_mutex_unlock(ph->right_mutex);
		if (ft_check_philo(ph, start_time, TAKE) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_check_philo(ph, start_time, TAKE) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (0);
	}
	else
		pthread_mutex_unlock(ph->right_mutex);
	return (-1);
}

int	ft_padlock_fmutex(pthread_mutex_t *fork, long *flag)
{
	int	valret;

	valret = pthread_mutex_lock(fork);
	if (valret != 0)
		return (valret);
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
	valret = pthread_mutex_unlock(fork);
	if (valret != 0)
		return (valret);
	return (EXIT_SUCCESS);
}

int	ft_check_die(t_philo *ph)
{
	pthread_mutex_lock(ph->flag_mutex);
	if (*(ph->flag) == DIE)
	{
		pthread_mutex_unlock(ph->flag_mutex);
		return (EXIT_FAILURE);
	}
	else
	{
		pthread_mutex_unlock(ph->flag_mutex);
		return (EXIT_SUCCESS);
	}
}
