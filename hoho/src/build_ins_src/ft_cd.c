/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:19:34 by payllana          #+#    #+#             */
/*   Updated: 2024/05/09 10:08:43 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_new_node(char *name, char *content)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (!new)
	{
		ft_err_msg("envp list", "Memory allocation failed", NULL);
		return (NULL);
	}
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_upd_env(t_envp *oldpwd, t_envp *pwd, t_envp *head)
{
	if (!oldpwd && !pwd)
		return (0);
	if (!oldpwd)
	{
		oldpwd = ft_last_env(head);
		oldpwd->next = ft_new_node("OLDPWD", NULL);
		if (!oldpwd->next)
			return (1);
		oldpwd = oldpwd->next;
		if (!oldpwd)
			return (ft_err_msg("env_list", "malloc failed", NULL), 1);
	}
	if (oldpwd && pwd)
	{
		if (pwd->content)
			ft_free_if(&oldpwd->content, ft_strdup(pwd->content));
		else
			ft_free_if(&oldpwd->content, NULL);
	}
	if (pwd)
		ft_free_if(&pwd->content, getcwd(NULL, PATH_MAX));
	return (0);
}

int	ft_chdir(char *new_path, t_envp *home, t_envp *oldpwd)
{
	if (!new_path || new_path[0] == '~')
	{
		if (!home || !home->content)
			return (ft_err_msg("cd", "HOME not set", NULL), 1);
		else if (home->content)
		{
			if (chdir(home->content))
				return (ft_err_msg("cd", "chdir", home->content), 1);
		}
	}
	else if (new_path && new_path[0] != '~')
	{
		if (new_path[0] == '-' && !new_path[1])
		{
			if (!oldpwd || !oldpwd->content)
				return (ft_err_msg("cd", "OLDPWD not set", NULL), 1);
			else if (oldpwd->content)
				new_path = ft_strdup(oldpwd->content);
		}
		if (chdir(new_path))
			return (ft_err_msg("cd", "No such file or directory", new_path), 1);
	}
	return (0);
}

int	ft_change_dir(t_shellinfo *mini, char *new_path)
{
	t_envp	*v_home;
	t_envp	*v_pwd;
	t_envp	*v_oldp;
	t_envp	*lst;

	v_home = NULL;
	v_pwd = NULL;
	v_oldp = NULL;
	lst = mini->env_lst;
	while (lst)
	{
		if (!ft_strncmp(lst->name, "PWD", ft_strlen(lst->name) + 1))
			v_pwd = lst;
		else if (!ft_strncmp(lst->name, "OLDPWD", ft_strlen(lst->name) + 1))
			v_oldp = lst;
		else if (!ft_strncmp(lst->name, "HOME", ft_strlen(lst->name) + 1))
			v_home = lst;
		lst = lst->next;
	}
	if (ft_chdir(new_path, v_home, v_oldp))
		return (1);
	if (ft_upd_env(v_oldp, v_pwd, mini->env_lst))
		return (1);
	return (0);
}

int	ft_work_cd(char **cmd, t_shellinfo *mini)
{
	if (!cmd[1])
		ft_change_dir(mini, 0);
	else if (cmd[2])
	{
		ft_err_msg("cd", "too many arguments", NULL);
		return (1);
	}
	else
	{
		if (ft_strlen(cmd[1]) >= PATH_MAX)
		{
			ft_err_msg("cd", "path too long", NULL);
			return (1);
		}
		if (ft_change_dir(mini, cmd[1]))
			return (1);
	}
	return (0);
}
