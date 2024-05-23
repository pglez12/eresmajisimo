/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:22:24 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 11:43:06 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_latoi(const char *str)
{
	size_t		i;
	long long	num;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

int	ft_iterate_check(char *cmd, int i)
{
	if (cmd)
	{
		if (cmd[i] == ' ')
		{
			while (cmd[i] == ' ' && cmd[i])
			{
				if (cmd[i + 1] == '\0')
					return (-1);
				if (cmd[i + 1] != ' ')
					return (2);
				i++;
			}
		}
	}
	return (0);
}

int	ft_contains_alpha(char *cmd)
{
	int	i;

	i = 0;
	i = ft_not_digit(cmd, i);
	if (i < 0)
		return (2);
	while (cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
		{
			if (ft_iterate_check(cmd, i) < 0)
				return (0);
			return (2);
		}
		i++;
	}
	return (0);
}

int	ft_check_error(char **cmd, long long ret)
{
	if (ret > LLONG_MAX || ret < LLONG_MIN)
	{
		ft_err_msg("exit", "numeric argument required", cmd[1]);
		ret = 255;
	}
	else if (ft_contains_alpha(cmd[1]))
	{
		ft_err_msg("exit", "numeric argument required", cmd[1]);
		ret = 2;
	}
	return (ret);
}

int	ft_exit(t_cmd *cmd, t_shellinfo *mini)
{
	long long	return_value;
	int			ret_err;

	if (!cmd->next && cmd->index == 0)
	{
		if (cmd->cmd[1])
		{
			return_value = ft_latoi(cmd->cmd[1]) & 0xff;
			ret_err = ft_check_error (cmd->cmd, return_value) & 0xff;
			if (ret_err != return_value)
				return (2);
			if (cmd->cmd[2])
				return (ft_err_msg("exit", "too many arguments", NULL), 1);
		}
		else
			return_value = 0;
		close(mini->std_fd[IN]);
		close(mini->std_fd[OUT]);
		ft_free_all(mini);
		exit((unsigned char)return_value);
	}
	else
		ft_exit_clean(mini, 0);
	return (0);
}
