/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:42:09 by payllana          #+#    #+#             */
/*   Updated: 2024/05/28 12:20:23 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long	ft_latoi(const char *str, int *flag)
{
	size_t				i;
	unsigned long long	num;

	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag[0] = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
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

int	ft_check_error(char **cmd, unsigned long long *ret, int flag)
{
	unsigned long long	llongmin;

	llongmin = (unsigned long long)LLONG_MAX + 1;
	if (ret[0] > LLONG_MAX && flag == 1)
	{
		ft_err_msg("exit", "numeric argument required", cmd[1]);
		return (2);
	}
	else if (flag == -1)
	{
		if (ret[0] > llongmin)
		{
			ft_err_msg("exit", "numeric argument required", cmd[1]);
			return (2);
		}
		else
			ret[0] = ret[0] * flag;
	}
	else if (ft_contains_alpha(cmd[1]))
	{
		ft_err_msg("exit", "numeric argument required", cmd[1]);
		return (2);
	}
	return (0);
}

int	ft_exit(t_cmd *cmd, t_shellinfo *mini)
{
	unsigned long long	return_value;
	int					ret_err;
	int					flag;

	flag = 1;
	if (!cmd->next && cmd->index == 0)
	{
		if (cmd->cmd[1])
		{
			return_value = ft_latoi(cmd->cmd[1], &flag);
			ret_err = ft_check_error (cmd->cmd, &return_value, flag);
			if (ret_err != 0)
				return_value = 2;
			if (cmd->cmd[2])
				return (ft_err_msg("exit", "too many arguments", NULL), 1);
		}
		else
			return_value = 0;
		ft_exit_clean(mini, (unsigned char)return_value);
	}
	else
		ft_exit_clean(mini, 0);
	return (0);
}
