/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:15:35 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:29:50 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_shared_vars(t_philo *philo, int size)
{
	int				*flag;
	pthread_mutex_t	*print;
	pthread_mutex_t	*count_mutex;
	long			*n_finish_eating;

	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	count_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	n_finish_eating = (long *)malloc(sizeof(long));
	flag = (int *)malloc(sizeof(int));
	if (!print || !count_mutex || !n_finish_eating || !flag)
		return (ft_putstr_fd("philo: malloc() failed\n", 2), 1);
	*n_finish_eating = ((*flag = 0), 0);
	if (pthread_mutex_init(print, NULL) != 0)
		return (ft_putstr_fd("philo: mutex_init() failed\n", 2), 1);
	if (pthread_mutex_init(count_mutex, NULL) != 0)
		return (ft_putstr_fd("philo: mutex_init() failed\n", 2), 1);
	while (--size >= 0)
	{
		philo[size].print = print;
		philo[size].count_mutex = count_mutex;
		philo[size].n_finish_eating = n_finish_eating;
		philo[size].flag = flag;
		philo[size].n_philo_eat = 0;
	}
	return (0);
}

static int	ft_init_indiv_vars(t_philo *philo, int size)
{
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*flag_mutex;
	int				i;

	flag_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!flag_mutex)
		return (ft_putstr_fd("philo: malloc() failed\n", 2), 1);
	if (pthread_mutex_init(flag_mutex, NULL) != 0)
		return (ft_putstr_fd("philo: mutex_init() failed\n", 2), 1);
	i = 0;
	while (i < size)
	{
		fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!fork_mutex)
			return (ft_putstr_fd("philo: malloc() failed\n", 2), 1);
		if (pthread_mutex_init(fork_mutex, NULL) != 0)
			return (ft_putstr_fd("philo: mutex_init() failed\n", 2), 1);
		philo[i].flag_mutex = flag_mutex;
		philo[i].right_mutex = fork_mutex;
		philo[(i + 1) % size].left_mutex = fork_mutex;
		philo[i].ph_name = i + 1;
		i ++;
	}
	return (0);
}

static int	ft_init_vars(t_philo *philo, int size, long *init_usec)
{
	if (ft_init_shared_vars(philo, size) != 0)
		return (1);
	if (ft_init_indiv_vars(philo, size) != 0)
		return (1);
	*init_usec = ft_time_now();
	if (*init_usec < 0)
		return (ft_putstr_fd("philo: gettimeofday() fail\n", 2), 1);
	return (0);
}

static void	ft_init_right_fork(t_philo *philo, long index)
{
	if (index % 2 == 0)
		*(philo->right_fork) = 0;
	else
		*(philo->right_fork) = -1;
}

t_philo	*ft_init_philo(int argc, char **argv)
{
	t_philo		*philo;
	t_params	info;
	long		init_usec;
	long		i;

	if (ft_init_params(argc, argv, &info))
		return (NULL);
	i = -1;
	philo = (t_philo *)malloc((sizeof(t_philo) * info.num_philo));
	if (!philo)
		return (ft_putstr_fd("philo: malloc() failed\n", 2), NULL);
	if (ft_init_vars(philo, info.num_philo, &init_usec) != 0)
		return (NULL);
	while (++i < info.num_philo)
	{
		philo[i].info = info;
		philo[i].init_usec = init_usec;
		philo[i].right_fork = (long *)malloc(sizeof(long));
		if (!philo[i].right_fork)
			return (ft_putstr_fd("philo: malloc() failed\n", 2), NULL);
		ft_init_right_fork(&(philo[i]), i);
		philo[(i + 1) % info.num_philo].left_fork = philo[i].right_fork;
	}
	return (philo);
}
