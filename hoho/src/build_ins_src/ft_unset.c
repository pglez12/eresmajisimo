/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:26:57 by payllana          #+#    #+#             */
/*   Updated: 2024/05/28 11:41:44 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************/
/*                                 FT_EXIT                                   */
/*****************************************************************************/

int	ft_not_digit(char *cmd, int i)
{
	if (cmd)
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] == '+' || cmd[i] == '-')
		{
			i++;
			if (cmd[i] == '+' || cmd[i] == '-')
				return (-1);
		}
	}
	return (i);
}

/*****************************************************************************/
/*                                FT_EXPORT                                  */
/*****************************************************************************/

void	ft_change_node_help(t_envp **lst, char *name, char *content)
{
	if (content)
	{
		free((*lst)->content);
		(*lst)->content = ft_strdup(content);
		free(content);
		free(name);
	}
	else
	{
		if (name)
			free(name);
		if (content)
			free(content);
		(*lst)->content = NULL;
	}
}

/*****************************************************************************/
/*                                 FT_UNSET                                  */
/*****************************************************************************/

int	ft_valid(char *str)
{
	int		valid;
	int		i;

	valid = 0;
	i = 0;
	if (!str)
		return (0);
	if (str[0] == '_' || ft_isalpha(str[0]))
		valid = 1;
	if (!valid)
		return (0);
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			valid = 0;
		i++;
	}
	return (valid);
}

static void	ft_del_env(t_shellinfo *mini, char *var)
{
	t_envp	*lst;

	lst = mini->env_lst;
	while (lst)
	{
		if (!ft_strncmp(lst->name, var, ft_strlen(lst->name) + 1))
		{
			free(lst->content);
			lst->content = NULL;
			break ;
		}
		lst = lst->next;
	}
}

int	ft_unset(char **cmd, t_shellinfo *mini, t_cmd *c)
{
	int		i;
	int		valret;

	i = 1;
	valret = 0;
	if (!c->next && c->index == 0)
	{
		while (cmd[i])
		{
			if (ft_valid(cmd[i]))
				ft_del_env(mini, cmd[i]);
			else
				valret = 0;
			i++;
		}
		return (valret);
	}
	else
		exit(valret);
}
