/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:59:30 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:30:41 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_pause_philo(t_philo *ph, long start_time, long cmp_time)
{
	long	usec;

	while (1)
	{
		pthread_mutex_lock(ph->flag_mutex);
		if (*(ph->flag) == DIE)
		{
			pthread_mutex_unlock(ph->flag_mutex);
			return ;
		}
		else
			pthread_mutex_unlock(ph->flag_mutex);
		usec = ft_time_now() - start_time;
		if (usec >= cmp_time || usec >= ph->info.time_to_die)
			return ;
		if (cmp_time - usec > K)
			usleep(500);
		else
			usleep(100);
	}
}

int	ft_check_philo(t_philo *ph, long start_time, int flag)
{
	t_msg	msg;

	if (ft_check_die(ph) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_set_phmsg(ph, &msg, flag) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_time_now() - start_time <= ph->info.time_to_die)
	{
		if (flag != NOT_PRINT)
			return (ft_philo_msg(ph, &msg));
	}
	else
	{
		pthread_mutex_lock(ph->flag_mutex);
		if (*(ph->flag) != DIE)
		{
			*(ph->flag) = DIE;
			printf("%ld %ld %s\n", (ft_time_now() - ph->init_usec)
				/ K, ph->ph_name, DIE_MSG);
		}
		pthread_mutex_unlock(ph->flag_mutex);
		return (EXIT_FAILURE);
	}
	return (0);
}

void	*ft_philo(void *input)
{
	t_philo	ph;
	long	start_time;

	ph = *(t_philo *)input;
	start_time = ft_time_now();
	while (1)
	{
		if (ft_eat(&ph, &start_time) == EXIT_FAILURE)
			return (NULL);
		if (ft_sleep(&ph, start_time) == EXIT_FAILURE)
			return (NULL);
		if (ft_think(&ph, start_time) == EXIT_FAILURE)
			return (NULL);
	}
}
