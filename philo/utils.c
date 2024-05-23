/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:11:42 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:32:24 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (1);
	return (time.tv_sec * K * K + time.tv_usec);
}

int	ft_turn_mic(char *argv, long *value, int mul)
{
	if (ft_check_int(argv, value))
		return (1);
	*value *= mul;
	return (0);
}
