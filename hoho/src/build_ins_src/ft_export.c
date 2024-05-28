/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:23:40 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/28 10:06:46 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_node(char *cmd, t_envp **lst)
{
	size_t	n;
	char	*name;
	char	*content;

	n = 0;
	name = ft_subenv(cmd, 0, '=', &n);
	content = ft_subenv(cmd, n + 1, '\0', &n);
	if (!name || !content)
		return (ft_err_msg("envp list", "Memory allocation failed", NULL), 1);
	while (*lst)
	{
		if (!ft_strncmp(name, (*lst)->name, ft_strlen((*lst)->name) + 1))
		{
			ft_change_node_help(lst, name, content);
			return (0);
		}
		(*lst) = (*lst)->next;
	}
	return (1);
}

int	ft_new_var(char *cmd, t_envp **lst, t_shellinfo *mini)
{
	size_t	n;
	t_envp	*new_node;
	char	*name;
	char	*content;

	n = 0;
	name = ft_subenv(cmd, 0, '=', &n);
	content = ft_subenv(cmd, n + 1, '\0', &n);
	new_node = ft_new_node(name, content);
	if (!new_node || !name || !content)
	{
		ft_err_msg("envp list", "Memory allocation failed", NULL);
		return (1);
	}
	ft_env_add_back(lst, new_node);
	mini->last_env = ft_last_env(*lst);
	return (0);
}

int	ft_present(char *name, t_envp *lst)
{
	while (lst)
	{
		if (!ft_strncmp(name, lst->name, ft_strlen(lst->name) + 1))
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	ft_export_args(char *cmd, t_envp **lst, t_shellinfo *mini)
{
	char	*name;
	size_t	ugh;
	int		valret;

	if (!cmd || !*lst)
		return (1);
	ugh = 0;
	valret = 0;
	name = ft_subenv(cmd, 0, '=', &ugh);
	if (ft_valid(name) && ft_contains(cmd))
	{
		if (!ft_present(name, *lst))
			valret = ft_change_node(cmd, lst);
		else
			valret = ft_new_var(cmd, lst, mini);
	}
	else if (!ft_valid(name))
	{
		valret = 1;
		ft_err_msg("export", "not a valid identifier", cmd);
	}
	free(name);
	return (valret);
}

int	ft_export(char **cmd, t_shellinfo *mini, t_cmd *c)
{
	unsigned int	i;
	t_envp			*lst;
	int				val;
	int				flag;

	lst = ((flag = 0), (val = 0), (i = 1), mini->env_lst);
	if (!cmd[1])
		ft_sort_env(mini);
	else
	{
		if (!c->next && c->index == 0)
		{
			while (cmd[i])
			{
				val = ft_export_args(cmd[i], &lst, mini);
				if (val > 0)
					flag = val;
				i++;
			}
			return (flag);
		}
	}
	if (!c->next && c->index == 0)
		return (val);
	exit(val);
}
