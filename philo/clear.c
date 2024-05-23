/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:15:42 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:51:56 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_philo(t_philo *philo)
{
	int	i;

	i = philo[0].info.num_philo;
	pthread_mutex_destroy(philo[0].print);
	pthread_mutex_destroy(philo[0].count_mutex);
	pthread_mutex_destroy(philo[0].flag_mutex);
	free(philo[0].print);
	free(philo[0].count_mutex);
	free(philo[0].flag_mutex);
	free(philo[0].n_finish_eating);
	free((void *)philo[0].flag);
	while (--i >= 0)
	{
		pthread_mutex_destroy(philo[i].left_mutex);
		free(philo[i].left_mutex);
		free(philo[i].left_fork);
	}
}

void	ft_free_id(pthread_t **id_threads, long size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (id_threads[i])
			free((void *)id_threads[i]);
		i ++;
	}
}
