/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:40:07 by payllana          #+#    #+#             */
/*   Updated: 2024/05/28 12:36:58 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_last_env(t_envp *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_env_add_back(t_envp **lst, t_envp *new)
{
	if (*lst)
		ft_last_env(*lst)->next = new;
	else
		*lst = new;
}

char	*ft_subenv(char *str, size_t ini, char del, size_t *n)
{
	char	*sub;
	size_t	i;

	if (!str)
		return (NULL);
	if (str && !str[ini] && str[ini] == '=')
		return (ft_strdup(""));
	sub = NULL;
	i = 0;
	while (str[ini + i] != del && str[ini + i] != '\0')
		i++;
	sub = (char *)malloc((i + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	*n = i;
	sub[i] = '\0';
	while (i-- > 0)
		sub[i] = str[ini + i];
	return (sub);
}

t_envp	*ft_append_node(char *var)
{
	size_t	n;
	t_envp	*new_node;
	char	*name;
	char	*content;

	n = 0;
	name = ft_subenv(var, 0, '=', &n);
	if (!ft_valid(name))
		return (free(name), NULL);
	content = ft_subenv(var, n + 1, '\0', &n);
	new_node = ft_new_node(name, content);
	if (!new_node || !name || !content)
	{
		ft_err_msg("envp list", "Memory allocation failed", NULL);
		return (NULL);
	}
	return (new_node);
}

int	ft_get_envp(char **envp, t_envp **lst, unsigned int a)
{
	unsigned int	i;
	t_envp			*node;

	node = NULL;
	if (!envp || !envp[0])
		return (0);
	if (a)
		i = a;
	else
		i = 0;
	while (envp[i])
	{
		node = ft_append_node(envp[i]);
		if (node)
			ft_env_add_back(lst, node);
		else if (!node)
			return (i);
		i ++;
	}
	return (0);
}
