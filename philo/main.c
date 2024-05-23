/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:16:48 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:51:26 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_creat_philos(t_philo *philo, pthread_t **id_th)
{
	long	i;

	i = -1;
	while (++i < philo[0].info.num_philo)
	{
		id_th[i] = (pthread_t *)malloc(sizeof(pthread_t));
		if (!id_th[i])
		{
			ft_putstr_fd("philo: malloc() failed\n", 2);
			return (ft_free_id(id_th, i), 1);
		}
		if (pthread_create(id_th[i], NULL, ft_philo, (void *)(&philo[i])) != 0)
		{
			ft_putstr_fd("philo: pthread_create() failed\n", 2);
			return (ft_free_id(id_th, i), 1);
		}
	}
	i = -1;
	while (++i < philo[0].info.num_philo)
	{
		if (pthread_join(*id_th[i], NULL) != 0)
			return (ft_putstr_fd("philo: pthread_join failed\n", 2), 1);
		free((void *)(id_th[i]));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	**id_th;
	int			valret;

	valret = 0;
	id_th = NULL;
	philo = ft_init_philo(argc, argv);
	if (!philo)
		return (1);
	id_th = (pthread_t **)malloc(sizeof(pthread_t *) * philo[0].info.num_philo);
	if (!id_th)
		valret = 1;
	if (valret == 0)
	{
		if (ft_creat_philos(philo, id_th) != 0)
		{
			ft_free_id(id_th, philo[0].info.num_philo);
			valret = 1;
		}
	}
	ft_free_philo(philo);
	free(id_th);
	free(philo);
	return (valret);
}
