/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:34:15 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 10:02:00 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[0] != '-')
		return (0);
	else if (flag[1] != 'n')
		return (0);
	i = i + 2;
	while (flag[i])
	{
		if (flag[i] == 'n' && flag[i])
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_print_echo(int i, char **cmd, int flag)
{
	while (cmd[i])
	{
		if (i > 1 && cmd[i + 1])
			printf("%s ", cmd[i]);
		else if (i > 1 && !cmd[i + 1])
			printf("%s", cmd[i]);
		else if (i > 0 && !flag && cmd[i + 1])
			printf("%s ", cmd[i]);
		else if (i > 0 && !flag && !cmd[i + 1])
			printf("%s", cmd[i]);
		i++;
	}
	if (!flag)
		printf("\n");
}

int	ft_echo(char **cmd)
{
	int	i;
	int	flag;

	i = ((flag = 0), 1);
	if (!cmd[1])
	{
		printf("\n");
		return (0);
	}
	while (!ft_strncmp(cmd[i], "-n", 2) && ft_is_flag(cmd[i]) && cmd[i])
	{
		if (!ft_is_flag(cmd[i]) || ft_strncmp(cmd[i], "-n", 2))
		{
			i++;
			if (!cmd[i])
				return (1);
			break ;
		}
		i++;
		if (!cmd[i])
			return (1);
		flag = 1;
	}
	ft_print_echo(i, cmd, flag);
	return (0);
}

int	ft_env(t_envp *lst, int flag)
{
	t_envp	*tmp;

	if (!lst)
		return (1);
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
		{
			if (!flag)
				printf("%s=%s\n", tmp->name, tmp->content);
			else
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_pwd(t_shellinfo *mini)
{
	char	*path;

	(void)mini;
	errno = 0;
	path = getcwd(NULL, PATH_MAX);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else
		printf("%s\n", strerror(errno));
	return (0);
}
