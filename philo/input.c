/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:23:13 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:29:52 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_int(const char *input, long *output)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (i == 0 && (input[i] == '-' || input[i] == '+'))
			i++;
		if (!ft_isdigit(input[i++]))
		{
			ft_putstr_fd("philo: not a number\n", 2);
			return (1);
		}
	}
	*output = ft_atol(input);
	if (*output < 0)
	{
		ft_putstr_fd("philo: don't input negative numbers\n", 2);
		return (1);
	}
	if (*output > INT_MAX || i > 12)
	{
		ft_putstr_fd("philo: not an integer\n", 2);
		return (1);
	}
	return (0);
}

int	ft_check_args(int argc, char **argv, t_params *info)
{
	if (!(argc == 5 || argc == 6))
	{
		if (argc < 5)
			ft_putstr_fd("philo: not enough arguments\n", 2);
		else if (argc > 6)
			ft_putstr_fd("philo: too many arguments\n", 2);
		return (1);
	}
	if (ft_check_int(argv[1], &(info->num_philo)))
		return (1);
	else
	{
		if (info->num_philo <= 0)
		{
			ft_putstr_fd("philo: not a valid number of philos\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_init_params(int argc, char **argv, t_params *info)
{
	int	i;

	i = 2;
	if (ft_check_args(argc, argv, info))
		return (1);
	if (ft_turn_mic(argv[i++], &(info->time_to_die), K))
		return (1);
	if (ft_turn_mic(argv[i++], &(info->time_to_eat), K))
		return (1);
	if (ft_turn_mic(argv[i++], &(info->time_to_sleep), K))
		return (1);
	if (argc == 6)
	{
		if (ft_turn_mic(argv[i], &(info->num_must_eat), 1))
			return (1);
		if (info->num_must_eat <= 0)
		{
			ft_putstr_fd("philo: not a valid number\n", 2);
			return (1);
		}
	}
	else
		info->num_must_eat = 0;
	return (0);
}
