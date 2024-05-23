/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:35:29 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:31:01 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep_msg(t_philo *ph, t_msg *msg)
{
	msg->msg = SLEEP_MSG;
	if (ph->info.num_must_eat > 0 && ph->info.num_must_eat == ph->n_philo_eat)
	{
		pthread_mutex_lock(ph->count_mutex);
		*(ph->n_finish_eating) = *(ph->n_finish_eating) + 1;
		if (*(ph->n_finish_eating) == ph->info.num_philo)
		{
			pthread_mutex_lock(ph->flag_mutex);
			*(ph->flag) = DIE;
			pthread_mutex_unlock(ph->flag_mutex);
		}
		pthread_mutex_unlock(ph->count_mutex);
	}
	return (EXIT_SUCCESS);
}

int	ft_set_phmsg(t_philo *ph, t_msg *msg, int flag)
{
	msg->flag = flag;
	msg->ph = ph->ph_name;
	msg->print = ph->print;
	if (flag == THINK)
		msg->msg = THINK_MSG;
	else if (flag == EAT)
	{
		msg->msg = EAT_MSG;
		ph->n_philo_eat++;
	}
	else if (flag == SLEEP)
	{
		if (ft_sleep_msg(ph, msg) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (flag == TAKE)
		msg->msg = TAKE_MSG;
	else if (flag == UNTAKE)
		msg->msg = UNTAKE_MSG;
	return (EXIT_SUCCESS);
}

int	ft_philo_msg(t_philo *ph, t_msg *msg)
{
	pthread_mutex_lock(ph->flag_mutex);
	if (*(ph->flag) == DIE)
	{
		pthread_mutex_unlock(ph->flag_mutex);
		return (EXIT_FAILURE);
	}
	else
	{
		pthread_mutex_lock(ph->print);
		msg->time = (ft_time_now() - ph->init_usec) / K;
		printf("%ld %ld %s\n", msg->time, msg->ph, msg->msg);
		pthread_mutex_unlock(ph->print);
		pthread_mutex_unlock(ph->flag_mutex);
		return (EXIT_SUCCESS);
	}
}
