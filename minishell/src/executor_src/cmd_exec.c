/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:02:15 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 11:41:05 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **cmd, t_shellinfo *mini, t_cmd *c)
{
	int	valret;

	valret = 0;
	if (!c->next && c->index == 0)
	{
		if (!ft_strncmp(cmd[0], "cd", 3))
		{
			valret = ft_work_cd(cmd, mini);
			return (valret);
		}
		else
		{
			if (access(cmd[1], F_OK))
			{
				ft_err_msg("cd", strerror(errno), cmd[1]);
				return (1);
			}
		}
		return (valret);
	}
	exit(valret);
}

int	ft_builtin_infork(t_cmd *c, t_shellinfo *mini)
{
	int	valret;

	valret = -1;
	if (!c->cmd || !c->cmd[0])
		return (1);
	if (!ft_strncmp(c->cmd[0], "echo", 5) || !ft_strncmp(c->cmd[0], "ECHO", 5))
		valret = ft_echo(c->cmd);
	else if (!ft_strncmp(c->cmd[0], "env", 4)
		|| !ft_strncmp(c->cmd[0], "ENV", 4))
		valret = ft_env(mini->env_lst, 0);
	else if (!ft_strncmp(c->cmd[0], "pwd", 4)
		|| !ft_strncmp(c->cmd[0], "PWD", 4))
		valret = ft_pwd(mini);
	else if (!ft_strncmp(c->cmd[0], "export", 7))
		valret = ft_export(c->cmd, mini, c);
	else if (!ft_strncmp(c->cmd[0], "cd", 3)
		|| !ft_strncmp(c->cmd[0], "CD", 3))
		valret = ft_cd(c->cmd, mini, c);
	else if (!ft_strncmp(c->cmd[0], "unset", 6))
		valret = ft_unset(c->cmd, mini, c);
	else if (!ft_strncmp(c->cmd[0], "exit", 5))
		valret = ft_exit(c, mini);
	if (valret != -1)
		exit(valret);
	return ((void) mini, valret);
}

int	ft_exec_builtin(t_cmd *c, t_shellinfo *mini, int flag)
{
	if (!c->cmd || !c->cmd[0])
		return (1);
	if (flag)
		return (ft_builtin_infork(c, mini));
	if (c->files && ft_check_file(c) != 0)
		return (errno);
	if (!ft_strncmp(c->cmd[0], "echo", 5) || !ft_strncmp(c->cmd[0], "ECHO", 5))
		return (ft_echo(c->cmd));
	else if (!ft_strncmp(c->cmd[0], "exit", 5))
		return (ft_exit(c, mini));
	else if (!ft_strncmp(c->cmd[0], "env", 4)
		|| !ft_strncmp(c->cmd[0], "ENV", 4))
		return (ft_env(mini->env_lst, 0));
	else if (!ft_strncmp(c->cmd[0], "pwd", 4)
		|| !ft_strncmp(c->cmd[0], "PWD", 4))
		return (ft_pwd(mini));
	else if (!ft_strncmp(c->cmd[0], "cd", 3)
		|| !ft_strncmp(c->cmd[0], "CD", 3))
		return (ft_cd(c->cmd, mini, c));
	else if (!ft_strncmp(c->cmd[0], "unset", 6))
		return (ft_unset(c->cmd, mini, c));
	else if (!ft_strncmp(c->cmd[0], "export", 7))
		return (ft_export(c->cmd, mini, c));
	(void) mini;
	return (-1);
}

void	ft_exit_clean(t_shellinfo *mini, int err)
{
	ft_free_all(mini);
	exit(err);
}

void	ft_exec_cmd(t_shellinfo *mini, t_cmd *cmds)
{
	if (ft_exec_builtin(cmds, mini, 1) == -1)
	{
		errno = 0;
		if (!mini->envp || !mini->envp[0])
		{
			printf("Deja de joder\n");
			exit (1);
		}
		cmds->path = ft_check_path(cmds, mini);
		if (!cmds->path)
		{
			ft_err_msg(cmds->cmd[0], "command not found", NULL);
			ft_exit_clean(mini, 127);
		}
		if (cmds->path)
		{
			execve(cmds->path, cmds->cmd, mini->envp);
			ft_err_msg(cmds->cmd[0], "command not found", NULL);
			ft_exit_clean(mini, 127);
		}
		ft_err_msg(cmds->cmd[0], "command not found", NULL);
		ft_exit_clean(mini, 127);
	}
	ft_exit_clean(mini, 1);
}
